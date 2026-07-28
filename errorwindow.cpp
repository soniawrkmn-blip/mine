#include "errorwindow.h"

void ErrorWindow::initWarningAndStr() {
    this->warning = new QPushButton;
    this->warning->setIcon(QIcon(":/icons/warning.png"));
    this->warning->setIconSize(QSize(32, 32));
    this->warning->setStyleSheet("border-radius: 32px; width: 32px; height:32px;");

    this->string = new QLabel("License error! Activate your license to continue working", this);
    this->string->setStyleSheet("color: #fff; font-size: 15px; font-weight: 500;");

    // Горизонтальный layout для кнопки и текста
    this->layout = new QHBoxLayout;
    this->layout->addWidget(this->warning);
    this->layout->addWidget(this->string);
    this->layout->addStretch(0);
    this->layout->setContentsMargins(20, 0, 0, 0);
}

void ErrorWindow::initActivBtn() {
    this->active = new QPushButton("Activate", this);
    this->active->setStyleSheet("background-color: gray; color: #fff; font-weight: 600; font-size: 15px; min-height: 30px; max-height: 30px; min-width: 100px; max-width: 100px;"
                                "border: 2px solid #fff; margin-bottom: 30px");

    this->activeWnd = new ActivateWindow(this);

    connect(this->active, &QPushButton::clicked, this->activeWnd, &ActivateWindow::show);
}

void ErrorWindow::initMainLayout() {
    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->addLayout(this->layout);
    this->mainLayout->addWidget(this->active);
    this->mainLayout->setAlignment(this->active, Qt::AlignHCenter);
}

ErrorWindow::ErrorWindow(QWidget* parent) : QDialog(parent)
{
    this->setStyleSheet("background-color: #101A28");

    this->initWarningAndStr();
    this->initActivBtn();
    this->initMainLayout();

    this->setLayout(this->mainLayout);
    this->setFixedSize(500, 200);

}
