#include "kycprocessor.h"
#include <QThread>
#include <QRandomGenerator>

KYCProcessor::KYCProcessor(QObject *parent)
    : QObject(parent), workerThread(new QThread(this)), worker(new KYCWorker())
{
    worker->moveToThread(workerThread);

    // Forward worker signals to external listeners
    connect(worker, &KYCWorker::processingStarted, this, &KYCProcessor::processingStarted);
    connect(worker, &KYCWorker::processingProgress, this, &KYCProcessor::processingProgress);
    connect(worker, &KYCWorker::processingCompleted, this, &KYCProcessor::processingCompleted);
    connect(worker, &KYCWorker::errorOccurred, this, &KYCProcessor::errorOccurred);
    connect(worker, &KYCWorker::identityGenerated, this, &KYCProcessor::identityGenerated);
    connect(worker, &KYCWorker::projectLoaded, this, &KYCProcessor::projectLoaded);
    connect(worker, &KYCWorker::videoInfo, this, &KYCProcessor::videoInfo);

    workerThread->start();
}

KYCProcessor::~KYCProcessor()
{
    if (workerThread) {
        workerThread->quit();
        workerThread->wait(3000);
    }
    delete worker; worker = nullptr;
}

bool KYCProcessor::generateIdentity(const QString& country, const QString& gender, const QString& passportTemplate)
{
    if (!validateInput("", country)) { emit errorOccurred("Invalid country selection"); return false; }

    // copy necessary data and queue work
    QVariantMap args;
    args["country"] = country;
    args["gender"] = gender;
    args["passport"] = passportTemplate;

    QMetaObject::invokeMethod(worker, "generateIdentityImpl", Qt::QueuedConnection,
                              Q_ARG(QString, country), Q_ARG(QString, gender), Q_ARG(QString, passportTemplate), Q_ARG(QVariantMap, QVariantMap()));
    return true;
}

bool KYCProcessor::generateIdentity(const QString& portraitPath, const QString& country, const QString& gender, const QString& passportTemplate)
{
    if (!validateInput(portraitPath, country)) { emit errorOccurred("Invalid portrait or country selection"); return false; }

    QVariantMap data;
    data["portrait"] = portraitPath;

    QMetaObject::invokeMethod(worker, "generateIdentityWithPortraitImpl", Qt::QueuedConnection,
                              Q_ARG(QString, portraitPath), Q_ARG(QString, country), Q_ARG(QString, gender), Q_ARG(QString, passportTemplate), Q_ARG(QVariantMap, data));
    return true;
}

QString KYCProcessor::getGeneratedIdentityInfo() const
{
    return generatedIdentityInfo;
}

bool KYCProcessor::createVideo(const QString& platform)
{
    if (platform.isEmpty()) { emit errorOccurred("Please select a platform"); return false; }
    QMetaObject::invokeMethod(worker, "doCreateVideo", Qt::QueuedConnection, Q_ARG(QString, platform));
    return true;
}

bool KYCProcessor::createDeepfakeVideo(const QString& portraitPath, const QString& platform, const QString& videoMode, const QString& quality)
{
    if (portraitPath.isEmpty() || platform.isEmpty()) { emit errorOccurred("Please select portrait and platform"); return false; }
    QVariantMap args;
    args["portrait"] = portraitPath;
    args["platform"] = platform;
    args["mode"] = videoMode;
    args["quality"] = quality;
    QMetaObject::invokeMethod(worker, "doCreateDeepfakeVideo", Qt::QueuedConnection, Q_ARG(QVariantMap, args));
    return true;
}

bool KYCProcessor::processDocument(const QString& documentPath)
{
    if (documentPath.isEmpty()) { emit errorOccurred("Please select a document"); return false; }
    QMetaObject::invokeMethod(worker, "doProcessDocument", Qt::QueuedConnection, Q_ARG(QString, documentPath));
    return true;
}

bool KYCProcessor::processKYCVideo(const QString& videoPath)
{
    if (videoPath.isEmpty()) { emit errorOccurred("Please select a video"); return false; }
    QMetaObject::invokeMethod(worker, "doProcessKYCVideo", Qt::QueuedConnection, Q_ARG(QString, videoPath));
    return true;
}

bool KYCProcessor::applyEffects(const QString& templatePath)
{
    if (templatePath.isEmpty()) { emit errorOccurred("Please select a template"); return false; }
    QMetaObject::invokeMethod(worker, "doApplyEffects", Qt::QueuedConnection, Q_ARG(QString, templatePath));
    return true;
}

bool KYCProcessor::saveProject(const QString& projectName)
{
    if (projectName.isEmpty()) { emit errorOccurred("Invalid project name"); return false; }

    QVariantMap vm;
    for (auto it = identityData.begin(); it != identityData.end(); ++it) vm[it.key()] = it.value();
    QMetaObject::invokeMethod(worker, "doSaveProject", Qt::QueuedConnection, Q_ARG(QString, projectName), Q_ARG(QVariantMap, vm));
    return true;
}

bool KYCProcessor::loadProject(const QString& projectName)
{
    if (projectName.isEmpty()) { emit errorOccurred("Invalid project name"); return false; }
    QMetaObject::invokeMethod(worker, "doLoadProject", Qt::QueuedConnection, Q_ARG(QString, projectName));
    return true;
}

bool KYCProcessor::connectCamera(const QString& docPath, const QString& videoPath, const QString& mode)
{
    if (docPath.isEmpty() || videoPath.isEmpty() || mode.isEmpty()) { emit errorOccurred("Please provide document, video, and mode"); return false; }
    QVariantMap args; args["doc"] = docPath; args["video"] = videoPath; args["mode"] = mode;
    QMetaObject::invokeMethod(worker, "doConnectCamera", Qt::QueuedConnection, Q_ARG(QVariantMap, args));
    return true;
}

bool KYCProcessor::validateInput(const QString& portraitPath, const QString& country)
{
    if (portraitPath.isEmpty() && !country.isEmpty()) return !country.isEmpty();
    if (portraitPath.isEmpty() && country.isEmpty()) return false;
    if (!portraitPath.isEmpty()) { QFileInfo fi(portraitPath); if (!fi.exists()) return false; }
    return !country.isEmpty();
}

QString KYCProcessor::generateUniqueID()
{
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
    quint32 rnd = QRandomGenerator::global()->bounded(10000);
    return QString("ID%1%2").arg(timestamp).arg(rnd);
}

QString KYCProcessor::generatePassportNumber(const QString& country)
{
    QString countryCode = country.left(2).toUpper();
    QString randomNum = QString::number(QRandomGenerator::global()->bounded(1000000)).rightJustified(6, '0');
    return countryCode + randomNum;
}

QString KYCProcessor::getCurrentDate()
{
    return QDateTime::currentDateTime().toString("dd/MM/yyyy");
}
