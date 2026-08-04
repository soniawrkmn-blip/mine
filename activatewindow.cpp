#include "activatewindow.h"
#include "license.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>

void ActivateWindow::initInputKeyContainer() {
    this->enterKey = new QLabel("Load Activation File:", this);
    this->enterKey->setStyleSheet("color: #fff; font-size: 15px; font-weight: 500; margin-left: 40px");

    // Remove the paste textbox; we will only allow loading a signed license file
    this->inputKey = nullptr;

    this->active = new QPushButton("Load License File", this);
    this->active->setStyleSheet("background-color: #2667fd; color: #fff; font-weight: 600; font-size: 15px; min-height: 25px; max-height: 25px; min-width: 140px; max-width: 140px;"
                                "border: 2px solid #fff; margin-top: 15px; margin-left: 40px;");

    connect(this->active, &QPushButton::clicked, this, [this] {
        QString filePath = QFileDialog::getOpenFileName(this, "Select License File", QDir::homePath(), "JSON Files (*.json);;All Files (*.*)");
        if (filePath.isEmpty()) return;

        LicenseManager::ActivationResult result = LicenseManager::activate(filePath);
        if (result.success) {
            QMessageBox msgBox;
            msgBox.setText("Activation Successful!\n\nWelcome to AMONEY ADVANCE KYC!");
            msgBox.setStyleSheet("background-color: white; color: black; font-size: 12px;");
            msgBox.setModal(true);
            msgBox.exec();

            this->active->setEnabled(false);
            this->active->setText("Activated");
            this->buy->setVisible(false);
            this->activeKey->setVisible(false);
            this->warning->setText("Your license is active for this device (HWID: " + result.hwid + ")");
            this->warning->setStyleSheet("color: #296303; font-weight: 600; margin-top: 15px; font-size: 11px;");

            accept();
        } else {
            QMessageBox msgBox;
            msgBox.setText(result.message);
            msgBox.setStyleSheet("background-color: white; color: black; font-size: 11px;");
            msgBox.setModal(true);
            msgBox.exec();

            // If an activation request file was created, open the folder so admin can see it during AnyDesk
            QString appData = LicenseManager::getAppDataPath();
            QString reqDir = appData + "/activation_requests";
            QDir d(reqDir);
            if (d.exists()) {
                QDesktopServices::openUrl(QUrl::fromLocalFile(d.absolutePath()));
            }
        }
    });

    this->activeKey = new QLabel("No key? Contact support:", this);
    this->activeKey->setStyleSheet("color: #fff; font-size: 15px; font-weight: 500; margin-top: 40px; margin-left: 40px;");
}

void ActivateWindow::initBuyKeyContainer() {
    this->buy = new QPushButton("Contact Support", this);
    this->buy->setStyleSheet("background-color: #296303; color: #fff; font-weight: 600; font-size: 15px; min-height: 25px; max-height: 25px; min-width: 120px; max-width: 120px;"
                             "border: 2px solid #fff; margin-top: 15px; margin-left: 40px;");

    connect(this->buy, &QPushButton::clicked, this, [] {
        QMessageBox msgBox;
        msgBox.setText("Contact @AmoneyTradingBot_Support on Telegram\n\nProvide your HWID shown below to get your activation key.\n\nEach device needs its own unique key.");
        msgBox.setStyleSheet("background-color: white; color: black; font-size: 12px;");
        msgBox.setModal(true);
        msgBox.exec();
    });
}

void ActivateWindow::initWarningText() {
    QString hwid = LicenseManager::getHWID();
    
    this->warning = new QLabel(this);
    this->warning->setStyleSheet("color: #fff; font-weight: 500; margin-top: 15px; font-size: 10px;");
    this->warning->setWordWrap(true);
    this->warning->setText("Your Device HWID: " + hwid + "\n\nThis key only works on THIS device.\nContact @AmoneyTradingBot_Support with this HWID to get your key.");
}

void ActivateWindow::initMainLayout() {
    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->addWidget(this->enterKey);
    // don't add inputKey (removed)
    this->mainLayout->addWidget(this->active);
    this->mainLayout->addWidget(this->activeKey);
    this->mainLayout->addWidget(this->buy);
    this->mainLayout->addWidget(this->warning);
    this->mainLayout->setAlignment(this->enterKey, Qt::AlignTop);
    this->mainLayout->setSpacing(0);
    this->mainLayout->addStretch(0);
    this->mainLayout->setContentsMargins(10, 50, 0, 0);
}

QJsonObject ActivateWindow::loadJsonFromFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr, "Error", "Cannot open the file for reading.");
        return QJsonObject();
    }

    QByteArray jsonData = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(jsonData);

    if (document.isObject()) {
        return document.object();
    }

    QMessageBox::critical(nullptr, "Error", "Invalid JSON format.");
    return QJsonObject();
}

ActivateWindow::ActivateWindow(QWidget* parent) : QDialog(parent)
{
    this->setWindowTitle("Activate AMONEY ADVANCE KYC");
    this->initInputKeyContainer();
    this->initBuyKeyContainer();
    this->initWarningText();
    this->initMainLayout();
    this->setLayout(this->mainLayout);
    this->setFixedSize(550, 400);
}
