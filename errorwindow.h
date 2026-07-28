#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include <stdafx.h>
#include <activatewindow.h>

class ErrorWindow : public QDialog
{
private:
    Q_OBJECT

    ActivateWindow* activeWnd;

    QPushButton* warning;
    QPushButton* active;

    QLabel* string;

    QHBoxLayout *layout;

    QVBoxLayout *mainLayout;

public:
    void initWarningAndStr();
    void initActivBtn();
    void initMainLayout();
    ErrorWindow(QWidget* parent = nullptr);
};

#endif // ERRORWINDOW_H
