#ifndef KYCPROCESSOR_H
#define KYCPROCESSOR_H

#include <stdafx.h>

class KYCProcessor : public QObject
{
    Q_OBJECT

public:
    explicit KYCProcessor(QObject *parent = nullptr);
    
    bool generateIdentity(const QString& country, const QString& gender, const QString& passportTemplate);
    bool generateIdentity(const QString& portraitPath, const QString& country, 
                         const QString& gender, const QString& passportTemplate);
    QString getGeneratedIdentityInfo() const;
    
    bool createVideo(const QString& platform);
    bool createDeepfakeVideo(const QString& portraitPath, const QString& platform,
                            const QString& videoMode, const QString& quality);
    
    bool processDocument(const QString& documentPath);
    bool processKYCVideo(const QString& videoPath);
    
    bool applyEffects(const QString& templatePath);
    
    bool saveProject(const QString& projectName);
    bool loadProject(const QString& projectName);
    
    bool connectCamera(const QString& docPath, const QString& videoPath, const QString& mode);
    
    bool validateInput(const QString& portraitPath, const QString& country);

signals:
    void processingStarted();
    void processingProgress(int percentage);
    void processingCompleted(bool success);
    void errorOccurred(const QString& error);

private:
    QString generatedIdentityInfo;
    QMap<QString, QString> identityData;
    
    QString generateUniqueID();
    QString generatePassportNumber(const QString& country);
    QString getCurrentDate();
};

#endif // KYCPROCESSOR_H