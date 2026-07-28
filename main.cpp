#include "mainwindow.h"
#include "activatewindow.h"
#include "license.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("AMONEY ADVANCE KYC");
    a.setApplicationVersion("3.2");
    
    qDebug() << "Starting AMONEY ADVANCE KYC...";
    qDebug() << "HWID:" << LicenseManager::getHWID();
    qDebug() << "Activated:" << LicenseManager::isActivated();
    qDebug() << "Saved HWID:" << LicenseManager::getActivatedHWID();
    
    if (!LicenseManager::isActivated()) {
        qDebug() << "Showing activation dialog...";
        ActivateWindow activateDialog;
        activateDialog.setWindowTitle("AMONEY ADVANCE KYC - Activation Required");
        int result = activateDialog.exec();
        qDebug() << "Dialog result:" << result;
        
        if (result != QDialog::Accepted) {
            return 0;
        }
        
        if (!LicenseManager::isActivated()) {
            return 0;
        }
    }
    
    MainWindow w;
    w.setWindowTitle("AMONEY ADVANCE KYC");
    w.show();
    w.setWindowIcon(QIcon(":/icons/logo.ico"));
    return a.exec();
}
