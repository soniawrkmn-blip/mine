#include "kycprocessor.h"
#include <QThread>
#include <QDateTime>
#include <QFileInfo>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

KYCProcessor::KYCProcessor(QObject *parent)
    : QObject(parent)
{
}

bool KYCProcessor::generateIdentity(const QString& country, const QString& gender, const QString& passportTemplate)
{
    if (!validateInput("", country)) {
        emit errorOccurred("Invalid country selection");
        return false;
    }
    
    emit processingStarted();
    
    try {
        identityData.clear();
        
        identityData["ID"] = generateUniqueID();
        identityData["Country"] = country;
        identityData["Gender"] = gender;
        identityData["PassportTemplate"] = passportTemplate;
        identityData["PassportNumber"] = generatePassportNumber(country);
        identityData["DateOfIssue"] = getCurrentDate();
        
        emit processingProgress(50);
        QThread::msleep(1000);
        
        emit processingProgress(100);
        
        generatedIdentityInfo = QString("Identity Generated:\n"
                                       "ID: %1\n"
                                       "Country: %2\n"
                                       "Gender: %3\n"
                                       "Passport: %4\n"
                                       "Passport#: %5\n"
                                       "Issued: %6")
            .arg(identityData["ID"],
                 identityData["Country"],
                 identityData["Gender"],
                 identityData["PassportTemplate"],
                 identityData["PassportNumber"],
                 identityData["DateOfIssue"]);
        
        emit processingCompleted(true);
        return true;
    }
    catch (const std::exception& e) {
        emit errorOccurred(QString("Error generating identity: %1").arg(e.what()));
        emit processingCompleted(false);
        return false;
    }
}

bool KYCProcessor::generateIdentity(const QString& portraitPath, const QString& country, 
                                   const QString& gender, const QString& passportTemplate)
{
    if (!validateInput(portraitPath, country)) {
        emit errorOccurred("Invalid portrait or country selection");
        return false;
    }
    
    emit processingStarted();
    
    try {
        identityData.clear();
        
        identityData["ID"] = generateUniqueID();
        identityData["Country"] = country;
        identityData["Gender"] = gender;
        identityData["PassportTemplate"] = passportTemplate;
        identityData["PassportNumber"] = generatePassportNumber(country);
        identityData["DateOfIssue"] = getCurrentDate();
        identityData["Portrait"] = portraitPath;
        
        emit processingProgress(50);
        QThread::msleep(1000);
        
        emit processingProgress(100);
        
        generatedIdentityInfo = QString("Identity Generated:\n"
                                       "ID: %1\n"
                                       "Country: %2\n"
                                       "Gender: %3\n"
                                       "Passport: %4\n"
                                       "Passport#: %5\n"
                                       "Issued: %6")
            .arg(identityData["ID"],
                 identityData["Country"],
                 identityData["Gender"],
                 identityData["PassportTemplate"],
                 identityData["PassportNumber"],
                 identityData["DateOfIssue"]);
        
        emit processingCompleted(true);
        return true;
    }
    catch (const std::exception& e) {
        emit errorOccurred(QString("Error generating identity: %1").arg(e.what()));
        emit processingCompleted(false);
        return false;
    }
}

QString KYCProcessor::getGeneratedIdentityInfo() const
{
    return generatedIdentityInfo;
}

bool KYCProcessor::createVideo(const QString& platform)
{
    if (platform.isEmpty()) {
        emit errorOccurred("Please select a platform");
        return false;
    }
    
    emit processingStarted();
    
    try {
        emit processingProgress(20);
        QThread::msleep(500);
        
        emit processingProgress(40);
        QThread::msleep(500);
        
        emit processingProgress(60);
        QThread::msleep(500);
        
        emit processingProgress(80);
        QThread::msleep(500);
        
        emit processingProgress(100);
        
        QString info = QString("Video Processing:\n"
                              "Platform: %1\n"
                              "Status: Completed")
            .arg(platform);
        
        generatedIdentityInfo = info;
        emit processingCompleted(true);
        return true;
    }
    catch (const std::exception& e) {
        emit errorOccurred(QString("Error creating video: %1").arg(e.what()));
        emit processingCompleted(false);
        return false;
    }
}

bool KYCProcessor::createDeepfakeVideo(const QString& portraitPath, const QString& platform,
                                      const QString& videoMode, const QString& quality)
{
    if (portraitPath.isEmpty() || platform.isEmpty()) {
        emit errorOccurred("Please select portrait and platform");
        return false;
    }
    
    emit processingStarted();
    
    try {
        emit processingProgress(20);
        QThread::msleep(500);
        
        emit processingProgress(40);
        QThread::msleep(500);
        
        emit processingProgress(60);
        QThread::msleep(500);
        
        emit processingProgress(80);
        QThread::msleep(500);
        
        emit processingProgress(100);
        
        QString info = QString("Video Processing:\n"
                              "Platform: %1\n"
                              "Mode: %2\n"
                              "Quality: %3\n"
                              "Status: Completed")
            .arg(platform, videoMode, quality);
        
        generatedIdentityInfo = info;
        emit processingCompleted(true);
        return true;
    }
    catch (const std::exception& e) {
        emit errorOccurred(QString("Error creating video: %1").arg(e.what()));
        emit processingCompleted(false);
        return false;
    }
}

bool KYCProcessor::processDocument(const QString& documentPath)
{
    if (documentPath.isEmpty()) {
        emit errorOccurred("Please select a document");
        return false;
    }
    
    QFileInfo fileInfo(documentPath);
    if (!fileInfo.exists()) {
        emit errorOccurred("Document file not found");
        return false;
    }
    
    emit processingStarted();
    emit processingProgress(50);
    QThread::msleep(500);
    emit processingProgress(100);
    emit processingCompleted(true);
    
    return true;
}

bool KYCProcessor::processKYCVideo(const QString& videoPath)
{
    if (videoPath.isEmpty()) {
        emit errorOccurred("Please select a video");
        return false;
    }
    
    QFileInfo fileInfo(videoPath);
    if (!fileInfo.exists()) {
        emit errorOccurred("Video file not found");
        return false;
    }
    
    emit processingStarted();
    emit processingProgress(50);
    QThread::msleep(500);
    emit processingProgress(100);
    emit processingCompleted(true);
    
    return true;
}

bool KYCProcessor::applyEffects(const QString& templatePath)
{
    if (templatePath.isEmpty()) {
        emit errorOccurred("Please select a template");
        return false;
    }
    
    emit processingStarted();
    emit processingProgress(50);
    QThread::msleep(500);
    emit processingProgress(100);
    emit processingCompleted(true);
    
    generatedIdentityInfo = "Effects applied to template: " + templatePath;
    return true;
}

bool KYCProcessor::saveProject(const QString& projectName)
{
    if (projectName.isEmpty()) {
        emit errorOccurred("Invalid project name");
        return false;
    }
    
    QFile file(projectName + ".kyc");
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject obj;
        QVariantMap variantMap;
        for (auto it = identityData.begin(); it != identityData.end(); ++it) {
            variantMap[it.key()] = it.value();
        }
        obj["identity"] = QJsonObject::fromVariantMap(variantMap);
        file.write(QJsonDocument(obj).toJson());
        file.close();
        return true;
    }
    
    emit errorOccurred("Failed to save project");
    return false;
}

bool KYCProcessor::loadProject(const QString& projectName)
{
    QFile file(projectName + ".kyc");
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        
        QJsonObject obj = doc.object();
        QVariantMap variantMap = obj["identity"].toObject().toVariantMap();
        
        identityData.clear();
        for (auto it = variantMap.begin(); it != variantMap.end(); ++it) {
            identityData[it.key()] = it.value().toString();
        }
        
        generatedIdentityInfo = QString("Identity Loaded:\n")
            .arg(identityData["ID"]);
        return true;
    }
    
    emit errorOccurred("Failed to load project");
    return false;
}

bool KYCProcessor::connectCamera(const QString& docPath, const QString& videoPath, const QString& mode)
{
    if (docPath.isEmpty() || videoPath.isEmpty() || mode.isEmpty()) {
        emit errorOccurred("Please provide document, video, and mode");
        return false;
    }
    
    emit processingStarted();
    emit processingProgress(50);
    QThread::msleep(500);
    emit processingProgress(100);
    emit processingCompleted(true);
    
    return true;
}

bool KYCProcessor::validateInput(const QString& portraitPath, const QString& country)
{
    if (portraitPath.isEmpty() && !country.isEmpty()) {
        // For RUN, country is required
        return !country.isEmpty();
    }
    if (portraitPath.isEmpty() && country.isEmpty()) {
        return false;
    }
    
    if (!portraitPath.isEmpty()) {
        QFileInfo fileInfo(portraitPath);
        if (!fileInfo.exists()) return false;
    }
    
    return !country.isEmpty();
}

QString KYCProcessor::generateUniqueID()
{
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
    uint random = qrand() % 10000;
    return QString("ID%1%2").arg(timestamp).arg(random);
}

QString KYCProcessor::generatePassportNumber(const QString& country)
{
    QString countryCode = country.left(2).toUpper();
    QString randomNum = QString::number(qrand() % 1000000).rightJustified(6, '0');
    return countryCode + randomNum;
}

QString KYCProcessor::getCurrentDate()
{
    return QDateTime::currentDateTime().toString("dd/MM/yyyy");
}