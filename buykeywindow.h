#ifndef BUYKEYWINDOW_H
#define BUYKEYWINDOW_H

#include <stdafx.h>
#include <activatewindow.h>
#include <confirmpayment.h>

class BuyKeyWindow : public QDialog
{
private:
    Q_OBJECT

    ConfirmPayment* confWind;

    QHBoxLayout* btnsLayout;
    QHBoxLayout* ref;
    QHBoxLayout* txnsAndPaid;

    QVBoxLayout* paidAndEmail;
    QVBoxLayout* transLayout;
    QVBoxLayout* mainLayout;

    QLabel* usdt;
    QLabel* refLab;
    QLabel* paid;
    QLabel* email;
    QLabel* trans;
    QLabel* warning;

    QTextEdit* price;
    QTextEdit* inputEmail;
    QTextEdit* inputTxns;

    QPushButton* month;
    QPushButton* month_3;
    QPushButton* year;
    QPushButton* lifetime;
    QPushButton* qr;
    QPushButton* copy;
    QPushButton* paidBtn;

    QPushButton* createPriceButton(const QString& text, QWidget* parent);

public:
    void initButtons();
    void initQrAndRef();
    void initPriceAndEmail();
    void initTranscAndPaid();
    void initWarning();
    void initMainLayout();
    BuyKeyWindow(QWidget *parent = nullptr);
};

#endif // BUYKEYWINDOW_H
