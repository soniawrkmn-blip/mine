#ifndef CONFIRMPAYMENT_H
#define CONFIRMPAYMENT_H

#include <stdafx.h>

class ConfirmPayment : public QDialog
{
private:
    QVBoxLayout* layout;
    QLabel* success;
    QPushButton* btn;

public:
    void initLabelAndBtn();
    void initLayout();
    ConfirmPayment(QWidget *parent = nullptr);
};

#endif // CONFIRMPAYMENT_H
