#include "kycworker.h"
#include <QThread>
#include <QDateTime>
#include <QFileInfo>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRandomGenerator>

static QString generateUniqueID_local()
{
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
    quint32 random = QRandomGenerator::global()->bounded(10000);
    return QString("ID%1%2").arg(timestamp).arg(random);
}

static QString generatePassportNumber_local(const QString &country)
{
    QString countryCode = country.left(2).toUpper();
    QString randomNum = QString::number(QRandomGenerator::global()->bounded(1000000)).rightJustified(6, '0');
    return countryCode + randomNum;
}

static QString getCurrentDate_local()
{
    return QDateTime::currentDateTime().toString("dd/MM/yyyy");
}

void KYCWorker::emitProgressThrottled(int percent)
{
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    if (now - m_lastProgressMs > 50 || percent == 100) {
        m_lastProgressMs = now;
        emit processingProgress(percent);
    }
}

void KYCWorker::generateIdentityImpl(const QString &country, const QString &gender, const QString &passportTemplate, const QVariantMap identityDataCopy)
{
    // Run on worker thread
    emit processingStarted();

    QVariantMap data = identityDataCopy;
    data["ID"] = generateUniqueID_local();
    data["Country"] = country;
    data["Gender"] = gender;
    data["PassportTemplate"] = passportTemplate;
    data["PassportNumber"] = generatePassportNumber_local(country);
    data["DateOfIssue"] = getCurrentDate_local();

    emitProgressThrottled(50);
    QThread::msleep(1000);
    emitProgressThrottled(100);

    QString generatedInfo = QString("Identity Generated:\n"
                                    "ID: %1\n"
                                    "Country: %2\n"
                                    "Gender: %3\n"
                                    "Passport: %4\n"
                                    "Passport#: %5\n"
                                    "Issued: %6")
            .arg(data.value("ID").toString(),
                 data.value("Country").toString(),
                 data.value("Gender").toString(),
                 data.value("PassportTemplate").toString(),
                 data.value("PassportNumber").toString(),
                 data.value("DateOfIssue").toString());

    emit identityGenerated(data, generatedInfo);
    emit processingCompleted(true);
}

void KYCWorker::generateIdentityWithPortraitImpl(const QString &portraitPath, const QString &country, const QString &gender, const QString &passportTemplate, const QVariantMap identityDataCopy)
{
    emit processingStarted();

    QVariantMap data = identityDataCopy;
    data["ID"] = generateUniqueID_local();
    data["Country"] = country;
    data["Gender"] = gender;
    data["PassportTemplate"] = passportTemplate;
    data["PassportNumber"] = generatePassportNumber_local(country);
    data["DateOfIssue"] = getCurrentDate_local();
    data["Portrait"] = portraitPath;

    emitProgressThrottled(50);
    QThread::msleep(1000);
    emitProgressThrottled(100);

    QString generatedInfo = QString("Identity Generated:\n"
                                    "ID: %1\n"
                                    "Country: %2\n"
                                    "Gender: %3\n"
                                    "Passport: %4\n"
                                    "Passport#: %5\n"
                                    "Issued: %6")
            .arg(data.value("ID").toString(),
                 data.value("Country").toString(),
                 data.value("Gender").toString(),
                 data.value("PassportTemplate").toString(),
                 data.value("PassportNumber").toString(),
                 data.value("DateOfIssue").toString());

    emit identityGenerated(data, generatedInfo);
    emit processingCompleted(true);
}

void KYCWorker::createVideoImpl(const QString &platform)
{
    if (platform.isEmpty()) {
        emit errorOccurred("Please select a platform");
        emit processingCompleted(false);
        return;
    }

    emit processingStarted();
    emitProgressThrottled(20);
    QThread::msleep(500);
    emitProgressThrottled(40);
    QThread::msleep(500);
    emitProgressThrottled(60);
    QThread::msleep(500);
    emitProgressThrottled(80);
    QThread::msleep(500);
    emitProgressThrottled(100);

    QString info = QString("Video Processing:\n"
                           "Platform: %1\n"
                           "Status: Completed").arg(platform);
    emit videoInfo(info);
    emit processingCompleted(true);
}

void KYCWorker::createDeepfakeVideoImpl(const QString &portraitPath, const QString &platform, const QString &videoMode, const QString &quality)
{
    if (portraitPath.isEmpty() || platform.isEmpty()) {
        emit errorOccurred("Please select portrait and platform");
        emit processingCompleted(false);
        return;
    }

    emit processingStarted();
    emitProgressThrottled(20);
    QThread::msleep(500);
    emitProgressThrottled(40);
    QThread::msleep(500);
    emitProgressThrottled(60);
    QThread::msleep(500);
    emitProgressThrottled(80);
    QThread::msleep(500);
    emitProgressThrottled(100);

    QString info = QString("Video Processing:\n"
                           "Platform: %1\n"
                           "Mode: %2\n"
                           "Quality: %3\n"
                           "Status: Completed").arg(platform, videoMode, quality);
    emit videoInfo(info);
    emit processingCompleted(true);
}

void KYCWorker::processDocumentImpl(const QString &documentPath)
{
    if (documentPath.isEmpty()) {
        emit errorOccurred("Please select a document");
        emit processingCompleted(false);
        return;
    }

    QFileInfo fileInfo(documentPath);
    if (!fileInfo.exists()) {
        emit errorOccurred("Document file not found");
        emit processingCompleted(false);
        return;
    }

    emit processingStarted();
    emitProgressThrottled(50);
    QThread::msleep(500);
    emitProgressThrottled(100);
    emit processingCompleted(true);
}

void KYCWorker::processKYCVideoImpl(const QString &videoPath)
{
    if (videoPath.isEmpty()) {
        emit errorOccurred("Please select a video");
        emit processingCompleted(false);
        return;
    }

    QFileInfo fileInfo(videoPath);
    if (!fileInfo.exists()) {
        emit errorOccurred("Video file not found");
        emit processingCompleted(false);
        return;
    }

    emit processingStarted();
    emitProgressThrottled(50);
    QThread::msleep(500);
    emitProgressThrottled(100);
    emit processingCompleted(true);
}

void KYCWorker::applyEffectsImpl(const QString &templatePath)
{
    if (templatePath.isEmpty()) {
        emit errorOccurred("Please select a template");
        emit processingCompleted(false);
        return;
    }

    emit processingStarted();
    emitProgressThrottled(50);
    QThread::msleep(500);
    emitProgressThrottled(100);

    QString info = QString("Effects applied to template: %1").arg(templatePath);
    emit videoInfo(info);
    emit processingCompleted(true);
}

void KYCWorker::saveProjectImpl(const QString &projectName, const QVariantMap &identityDataCopy)
{
    if (projectName.isEmpty()) {
        emit errorOccurred("Invalid project name");
        emit processingCompleted(false);
        return;
    }

    QFile file(projectName + ".kyc");
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject obj;
        obj["identity"] = QJsonObject::fromVariantMap(identityDataCopy);
        file.write(QJsonDocument(obj).toJson());
        file.close();
        emit processingCompleted(true);
        return;
    }

    emit errorOccurred("Failed to save project");
    emit processingCompleted(false);
}

void KYCWorker::loadProjectImpl(const QString &projectName)
{
    if (projectName.isEmpty()) {
        emit errorOccurred("Invalid project name");
        emit processingCompleted(false);
        return;
    }

    QFile file(projectName + ".kyc");
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();

        QJsonObject obj = doc.object();
        QVariantMap variantMap = obj["identity"].toObject().toVariantMap();

        emit projectLoaded(variantMap);
        emit processingCompleted(true);
        return;
    }

    emit errorOccurred("Failed to load project");
    emit processingCompleted(false);
}

void KYCWorker::connectCameraImpl(const QString &docPath, const QString &videoPath, const QString &mode)
{
    if (docPath.isEmpty() || videoPath.isEmpty() || mode.isEmpty()) {
        emit errorOccurred("Please provide document, video, and mode");
        emit processingCompleted(false);
        return;
    }

    emit processingStarted();
    emitProgressThrottled(50);
    QThread::msleep(500);
    emitProgressThrottled(100);
    emit processingCompleted(true);
}
