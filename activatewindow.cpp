#include "activatewindow.h"
#include "license.h"
#include <QMessageBox>

void ActivateWindow::initInputKeyContainer() {
    this->enterKey = new QLabel("Enter Activation Key:", this);
    this->enterKey->setStyleSheet("color: #fff; font-size: 15px; font-weight: 500; margin-left: 40px");

    this->inputKey = new QTextEdit(this);
    this->inputKey->setStyleSheet("margin-top: 15px; max-height: 20px; max-width: 300px; background-color: #fff; margin-left: 40px;");
    this->inputKey->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->inputKey->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->inputKey->setWordWrapMode(QTextOption::NoWrap);

    this->active = new QPushButton("Activate", this);
    this->active->setStyleSheet("background-color: #2667fd; color: #fff; font-weight: 600; font-size: 15px; min-height: 25px; max-height: 25px; min-width: 100px; max-width: 100px;"
                                "border: 2px solid #fff; margin-top: 15px; margin-left: 40px;");

    connect(this->active, &QPushButton::clicked, this, [this] {
        QString key = this->inputKey->toPlainText().trimmed();
        if (key.isEmpty()) {
            QMessageBox msgBox;
            msgBox.setText("Please enter an activation key!");
            msgBox.setStyleSheet("background-color: white; color: black; font-size: 12px;");
            msgBox.setModal(true);
            msgBox.exec();
            return;
        }

        LicenseManager::ActivationResult result = LicenseManager::activate(key);
        
        if (result.success) {
            QMessageBox msgBox;
            msgBox.setText("Activation Successful!\n\nWelcome to AMONEY ADVANCE KYC!");
            msgBox.setStyleSheet("background-color: white; color: black; font-size: 12px;");
            msgBox.setModal(true);
            msgBox.exec();
            
            this->inputKey->clear();
            this->inputKey->setEnabled(false);
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
    this->mainLayout->addWidget(this->inputKey);
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
