#include "buykeywindow.h"

QJsonObject json = ActivateWindow::loadJsonFromFile(":/settings.json");

QPushButton* BuyKeyWindow::createPriceButton(const QString& text, QWidget* parent) {
    QPushButton* button = new QPushButton(text, parent);
    button->setStyleSheet("background-color: gray; color: #fff; font-weight: 600; font-size: 15px; "
                          "min-height: 50px; max-height: 50px; min-width: 100px; max-width: 100px; "
                          "border: 2px solid #fff; margin-right: 15px;");
    return button;
}

void BuyKeyWindow::initButtons() {
    this->btnsLayout = new QHBoxLayout;

    this->setContentsMargins(30, 30, 30, 30);

    this->price = new QTextEdit(this);
    this->price->setStyleSheet("background-color: #fff; color: #000; font-size: 14px; font-weight: 500; "
                               "max-width: 110px; max-height: 20px; margin-top: 10px;");
    this->price->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->price->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->month = createPriceButton(json.value("1month").toString(), this);
    this->btnsLayout->addWidget(this->month);

    this->month_3 = createPriceButton(json.value("3month").toString(), this);
    this->btnsLayout->addWidget(this->month_3);

    this->year = createPriceButton(json.value("1year").toString(), this);
    this->btnsLayout->addWidget(this->year);

    this->lifetime = createPriceButton(json.value("lifetime").toString(), this);
    this->btnsLayout->addWidget(this->lifetime);

    this->btnsLayout->setAlignment(Qt::AlignHCenter);
}

void BuyKeyWindow::initQrAndRef() {
    this->qr = new QPushButton(this);
    this->qr->setIcon(QIcon(":/qr/QR.png"));
    this->qr->setIconSize(QSize(103, 101));
    this->qr->setStyleSheet("max-width: 103px; max-height: 101px; margin-top: 30px");

    this->usdt = new QLabel(json.value("usdt").toString(), this);
    this->usdt->setStyleSheet("color: #fff; font-size: 15px; font-weight: 500;");

    this->refLab = new QLabel(json.value("reference").toString(), this);
    this->refLab->setStyleSheet("color: #fff; font-size: 15px; font-weight: 500; text-decoration: underline; margin-left: 10px; margin-right:10px");

    this->copy = new QPushButton("Copy", this);
    this->copy->setStyleSheet("background-color: #2667fd; color: #fff; font-weight: 600; font-size: 15px; min-height: 30px; max-height: 30px; min-width: 90px; "
                              "max-width: 90px; border: 2px solid #fff;");

    connect(this->copy, &QPushButton::clicked, this, [this] {
        QString textToCopy = this->refLab->text();

        // Получаем объект буфера обмена
        QClipboard *clipboard = QApplication::clipboard();

        // Копируем текст в буфер обмена
        clipboard->setText(textToCopy);

        // (Необязательно) Можно добавить всплывающее уведомление или другое поведение после копирования
        QMessageBox msg;
        msg.setText("Text copied to clipboard!");
        msg.setStyleSheet("background-color: #fff, color:#000");
        msg.setModal(true);
        msg.exec();
    });

    this->ref = new QHBoxLayout;
    this->ref->addWidget(this->usdt);
    this->ref->addWidget(this->refLab);
    this->ref->addWidget(this->copy);
    this->ref->addStretch(0);
    this->ref->setContentsMargins(50,20,0,0);
}

void BuyKeyWindow::initPriceAndEmail() {
    this->paid = new QLabel("To be paid:", this);
    this->paid->setStyleSheet("color: #fff; font-size: 14px; font-weight: 500;");

    this->email = new QLabel("Email:", this);
    this->email->setStyleSheet("color: #fff; font-size: 14px; font-weight: 500; margin-top: 10px");

    this->inputEmail = new QTextEdit(this);
    this->inputEmail->setStyleSheet("background-color: #fff; color: #000; font-size: 14px; font-weight: 500; max-width: 200px; max-height: 20px; "
                                    "margin-top: 10px;");
    this->inputEmail->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->inputEmail->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    this->paidAndEmail = new QVBoxLayout;
    this->paidAndEmail->addWidget(this->paid);
    this->paidAndEmail->addWidget(this->price);
    this->paidAndEmail->addWidget(this->email);
    this->paidAndEmail->addWidget(this->inputEmail);
    this->paidAndEmail->setSpacing(0);
    this->paidAndEmail->addStretch(0);
}

void BuyKeyWindow::initTranscAndPaid() {
    this->trans = new QLabel("Transcation(Txns):", this);
    this->trans->setStyleSheet("color: #fff; font-size: 14px; font-weight: 500; margin-top: 10px");

    this->inputTxns = new QTextEdit(this);
    this->inputTxns->setStyleSheet("background-color: #fff; color: #000; font-size: 14px; font-weight: 500; max-width: 220px; max-height: 20px; "
                                   "margin-top: 10px;");
    this->inputTxns->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->inputTxns->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->paidBtn = new QPushButton("I paid", this);
    this->paidBtn->setStyleSheet("background-color: #296303; color: #fff; font-weight: 600; font-size: 15px; min-height: 50px; max-height: 50px; "
                                 "min-width: 120px; max-width: 120px; border: 2px solid #fff; margin-top: 10px");

    this->confWind = new ConfirmPayment(this);
    connect(this->paidBtn, &QPushButton::clicked, this->confWind, &ConfirmPayment::show);

    this->transLayout = new QVBoxLayout;
    this->transLayout->addWidget(this->trans);
    this->transLayout->addWidget(this->inputTxns);
    this->transLayout->addWidget(this->paidBtn);
    this->transLayout->setSpacing(0);
    this->transLayout->addStretch(0);

    this->txnsAndPaid = new QHBoxLayout;
    this->txnsAndPaid->addLayout(this->paidAndEmail);
    this->txnsAndPaid->addLayout(this->transLayout);
}

void BuyKeyWindow::initWarning() {
    this->warning = new QLabel(json.value("after-payment").toString(), this);
    this->warning->setStyleSheet("color: #fff; font-weight: 500; font-size: 13px; margin-top: 15px;");
}

void BuyKeyWindow::initMainLayout() {
    // Создаем основной вертикальный layout
    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->addLayout(this->btnsLayout);  // Добавляем кнопки
    this->mainLayout->addWidget(this->qr);          // Добавляем кнопку с QR
    this->mainLayout->addLayout(this->ref);
    this->mainLayout->addLayout(this->txnsAndPaid);
    this->mainLayout->addWidget(this->warning);

    // Выравниваем все содержимое по центру (как по горизонтали, так и по вертикали)
    this->mainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft); // Центрируем весь layout по горизонтали
    this->mainLayout->setAlignment(qr, Qt::AlignCenter);     // Выровнять по верху

}

BuyKeyWindow::BuyKeyWindow(QWidget *parent) : QDialog(parent)
{
    this->initButtons();
    this->initQrAndRef();
    this->initPriceAndEmail();
    this->initTranscAndPaid();
    this->initWarning();
    this->initMainLayout();

    this->setLayout(this->mainLayout);

    this->setFixedSize(810, 600);
}
