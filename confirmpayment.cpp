#include "confirmpayment.h"

void ConfirmPayment::initLabelAndBtn() {
    this->success = new QLabel("Payment Confirm", this);
    this->success->setStyleSheet("color: #fff; font-size: 14px; font-weight: 500; margin-top: 40px;");

    this->btn = new QPushButton("I paid", this);
    this->btn->setStyleSheet("background-color: #296303; color: #fff; font-weight: 600; font-size: 15px; min-height: 30px; max-height: 30px; min-width: 90px; max-width: 90px;"
                             "border: 2px solid #fff; margin-top: 25px;");

    connect(this->btn, &QPushButton::clicked, this, &ConfirmPayment::close);
}

void ConfirmPayment::initLayout() {
    this->layout = new QVBoxLayout(this);
    this->layout->addWidget(this->success);
    this->layout->addWidget(this->btn);
    this->layout->addStretch(0);
    this->layout->setSpacing(0);
    this->layout->setAlignment(Qt::AlignHCenter);
    this->layout->setAlignment(this->btn, Qt::AlignHCenter);
}

ConfirmPayment::ConfirmPayment(QWidget *parent) : QDialog(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);

    this->initLabelAndBtn();
    this->initLayout();

    this->setLayout(this->layout);
    this->setFixedSize(300, 200);
}
