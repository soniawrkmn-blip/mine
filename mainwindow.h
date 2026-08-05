#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdafx.h>
#include <errorwindow.h>
#include <kycprocessor.h>
#include <license.h>
#include <QVariantMap>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    ErrorWindow* errWindow;

    QWidget *identification;
    QWidget *deepfake;
    QWidget *virtualCamera;

    QLabel *portrait;
    QLabel *identitiy;
    QLabel *passTemp;
    QLabel *portrait_2;
    QLabel *platform;
    QLabel *videoMode;
    QLabel* qualityMode;
    QLabel* recomendation;
    QLabel* identDoc;
    QLabel* videoKYC;

    QPushButton* browse;
    QPushButton* none;
    QPushButton* effect;
    QPushButton* run;
    QPushButton* getSmt;
    QPushButton* save;
    QPushButton* browse_2;
    QPushButton* createVideo;
    QPushButton* emptyBtn;
    QPushButton* browseDoc;
    QPushButton* browseKYC;
    QPushButton* connectBr;
    QPushButton* connectEm;

    QLabel *frame;
    QFrame *frame_2;
    QLabel *frame_1;
    QLabel *frame_2_1;

    QComboBox *countryComboBox;

    QCheckBox *menCheckBox;
    QCheckBox *womenCheckBox;
    QCheckBox *fastMode;
    QCheckBox *proMode;
    QCheckBox *expertMode;
    QCheckBox *sd;
    QCheckBox *mp4;
    QCheckBox *hdMp4;

    QHBoxLayout *checkBoxsLayout;
    QHBoxLayout *btnsLayout;
    QHBoxLayout *mainLayout;
    QHBoxLayout *mainLayout_2;
    QHBoxLayout* videoModesLayout;
    QHBoxLayout* qualityModesLayout;
    QHBoxLayout* docLayout;
    QHBoxLayout* KYCLayout;
    QHBoxLayout* connectLayout;

    QVBoxLayout *layout1;
    QVBoxLayout *layout1_2;
    QVBoxLayout *layout1_3;
    QVBoxLayout *layout2;
    QVBoxLayout *layout2_1;
    QVBoxLayout *layout2_2;
    QVBoxLayout *layout3;
    QVBoxLayout* identificationLayout;
    QVBoxLayout* deepfakeLayout;
    QVBoxLayout* identityLayout;
    QVBoxLayout* cameraLayout;

    QComboBox *passportComboBox;

    QListWidget* listWidget;

    QTextEdit* editArea;
    QTextEdit* inputDoc;
    QTextEdit* inputKYC;

    QTabWidget *tabWidget;

    QVector<QPushButton*> btns;

    QMenu *menu;

    KYCProcessor* kycProcessor;

    // Latest generated identity (filled when identityGenerated signal arrives)
    QVariantMap currentIdentity;

public:
    MainWindow(QWidget *parent = nullptr);
    void initPortraitAndIdentity();
    void initPassTemplate();
    void initBtnsAndFrame();
    void initIdentificationPage();
    void initPrtAndFr();
    void initKYCAndList();
    void initModes();
    void initDeepfakePage();
    void initDocumentAndKYC();
    void initButtons();
    void initVirtualCameraPage();
    ~MainWindow();

private slots:
    // Identification Page Slots
    void onBrowsePortrait();
    void onGenerateIdentity();
    void onRunProcess();
    void onApplyEffect();
    void onSaveIdentity();

    // Deepfake Page Slots
    void onBrowsePortrait2();
    void onCreateDeepfakeVideo();

    // Virtual Camera Page Slots
    void onBrowseDocument();
    void onBrowseKYCVideo();
    void onConnectBrowser();
    void onConnectEmulator();

    // Processing result handlers
    void onProcessingProgress(int progress);
    void onProcessingCompleted(bool success);
    void onProcessingError(const QString& error);

    // Data-carrying handlers from worker
    void onIdentityGenerated(const QVariantMap& identityData, const QString& generatedInfo);
    void onVideoInfo(const QString& info);
};

#endif // MAINWINDOW_H
