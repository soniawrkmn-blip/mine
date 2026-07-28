#ifndef ACTIVATEWINDOW_H
#define ACTIVATEWINDOW_H

#include <stdafx.h>
#include <buykeywindow.h>

class ActivateWindow : public QDialog
{
private:
    Q_OBJECT

    QLabel* enterKey;
    QLabel* activeKey;
    QLabel* warning;

    QTextEdit* inputKey;

    QPushButton* active;
    QPushButton* buy;

    QVBoxLayout* mainLayout;

public:
    void initInputKeyContainer();
    void initBuyKeyContainer();
    void initWarningText();
    void initMainLayout();
    static QJsonObject loadJsonFromFile(const QString &fileName);
    explicit ActivateWindow(QWidget* parent = nullptr);
};

#endif // ACTIVATEWINDOW_H
