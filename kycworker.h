#ifndef KYCWORKER_H
#define KYCWORKER_H

#include <QObject>
#include <QString>
#include <QVariantMap>

class KYCWorker : public QObject
{
    Q_OBJECT
public:
    explicit KYCWorker(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void generateIdentityImpl(const QString& country, const QString& gender, const QString& passportTemplate, const QVariantMap identityDataCopy);
    void generateIdentityWithPortraitImpl(const QString& portraitPath, const QString& country, const QString& gender, const QString& passportTemplate, const QVariantMap identityDataCopy);
    void createVideoImpl(const QString& platform);
    void createDeepfakeVideoImpl(const QString& portraitPath, const QString& platform, const QString& videoMode, const QString& quality);
    void processDocumentImpl(const QString& documentPath);
    void processKYCVideoImpl(const QString& videoPath);
    void applyEffectsImpl(const QString& templatePath);
    void saveProjectImpl(const QString& projectName, const QVariantMap& identityDataCopy);
    void loadProjectImpl(const QString& projectName);
    void connectCameraImpl(const QString& docPath, const QString& videoPath, const QString& mode);

signals:
    void processingStarted();
    void processingProgress(int percentage);
    void processingCompleted(bool success);
    void errorOccurred(const QString& error);

private:
    // helper: throttle progress emission
    void emitProgressThrottled(int percent);
};

#endif // KYCWORKER_H
