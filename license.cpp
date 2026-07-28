#include "license.h"
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QSysInfo>
#include <QNetworkInterface>
#include <QDateTime>

const QString LicenseManager::ADMIN_SECRET = "AMONEY_ADVANCE_2026_HWID_SECRET";
const QString LicenseManager::ACTIVATION_FILE = "activation.dat";

QString LicenseManager::getHWID() {
    QString appData = getAppDataPath();
    QString hwidFile = appData + "/hwid.dat";
    
    QFile f(hwidFile);
    if (f.exists()) {
        f.open(QIODevice::ReadOnly);
        QString id = f.readAll().trimmed();
        f.close();
        if (!id.isEmpty()) return id;
    }
    
    // Generate HWID from system components
    QString cpuId = QSysInfo::currentCpuArchitecture();
    QString machineId = QSysInfo::machineUniqueId();
    QString bootId = QSysInfo::bootUniqueId();
    
    // Add MAC addresses
    QString macs;
    for (const QNetworkInterface &iface : QNetworkInterface::allInterfaces()) {
        if (!(iface.flags() & QNetworkInterface::IsLoopBack) && 
            (iface.flags() & QNetworkInterface::IsUp)) {
            macs += iface.hardwareAddress();
        }
    }
    
    QString raw = cpuId + "|" + machineId + "|" + bootId + "|" + macs + "|" + ADMIN_SECRET;
    QByteArray hash = QCryptographicHash::hash(raw.toUtf8(), QCryptographicHash::Sha256);
    QString hwid = hash.toHex().left(32).toUpper();
    
    // Format: XXXX-XXXX-XXXX-XXXX (32 chars = 8+8+8+8 with 3 dashes)
    hwid.insert(8, '-');
    hwid.insert(17, '-');
    hwid.insert(26, '-');
    
    // Save for consistency
    QDir().mkpath(appData);
    f.setFileName(hwidFile);
    if (f.open(QIODevice::WriteOnly)) {
        f.write(hwid.toUtf8());
        f.close();
    }
    
    return hwid;
}

QString LicenseManager::getAppDataPath() {
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/AMONEY_ADVANCE_KYC";
}

bool LicenseManager::isActivated() {
    QString currentHWID = getHWID();
    QString activatedHWID = loadActivatedHWID();
    return currentHWID == activatedHWID && !activatedHWID.isEmpty();
}

LicenseManager::ActivationResult LicenseManager::activate(const QString& key) {
    ActivationResult result;
    result.hwid = getHWID();
    
    if (validateKey(key, result.hwid)) {
        if (saveActivatedHWID(result.hwid)) {
            result.success = true;
            result.message = "Activation successful! Welcome to AMONEY ADVANCE KYC.";
        } else {
            result.message = "Activation valid but failed to save. Try running as Administrator.";
        }
    } else {
        result.message = "Invalid activation key for this device.\nYour HWID: " + result.hwid + "\nContact @AmoneyTradingBot_Support with this HWID.";
    }
    return result;
}

void LicenseManager::deactivate() {
    QString appData = getAppDataPath();
    QFile f(appData + "/" + ACTIVATION_FILE);
    if (f.exists()) f.remove();
}

QString LicenseManager::getActivatedHWID() {
    return loadActivatedHWID();
}

QString LicenseManager::generateAdminKey(const QString& hwid) {
    QString data = hwid + "|" + ADMIN_SECRET;
    QByteArray hash = QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Sha256);
    QString key = hash.toHex().left(32).toUpper();
    
    key.insert(8, '-');
    key.insert(17, '-');
    key.insert(26, '-');
    
    return key;
}

bool LicenseManager::validateKey(const QString& key, const QString& hwid) {
    QString cleanKey = key;
    cleanKey.remove('-');
    cleanKey = cleanKey.toUpper();
    
    QString expected = generateAdminKey(hwid);
    QString cleanExpected = expected;
    cleanExpected.remove('-');
    cleanExpected = cleanExpected.toUpper();
    
    return cleanKey == cleanExpected;
}

QString LicenseManager::loadActivatedHWID() {
    QString appData = getAppDataPath();
    QFile f(appData + "/" + ACTIVATION_FILE);
    if (!f.exists()) return "";
    
    if (!f.open(QIODevice::ReadOnly)) return "";
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    f.close();
    
    if (!doc.isObject()) return "";
    return doc.object().value("hwid").toString();
}

bool LicenseManager::saveActivatedHWID(const QString& hwid) {
    QString appData = getAppDataPath();
    QDir().mkpath(appData);
    QFile f(appData + "/" + ACTIVATION_FILE);
    
    if (!f.open(QIODevice::WriteOnly)) return false;
    
    QJsonObject obj;
    obj["hwid"] = hwid;
    obj["activated"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    
    f.write(QJsonDocument(obj).toJson());
    f.close();
    return true;
}