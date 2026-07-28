#include "license.h"
#include <QCoreApplication>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    
    // Check for -l flag manually
    QStringList args = a.arguments();
    if (args.contains("-l") || args.contains("--list")) {
        QString hwid = LicenseManager::getHWID();
        std::cout << "Current Device HWID: " << hwid.toStdString() << "\n";
        std::cout << "\nGive this HWID to admin to generate activation key.\n";
        return 0;
    }
    
    // Check for -h <hwid>
    QString hwid;
    for (int i = 1; i < args.size(); ++i) {
        if ((args[i] == "-h" || args[i] == "--hwid") && i + 1 < args.size()) {
            hwid = args[i + 1];
            break;
        }
    }
    
    if (hwid.isEmpty()) {
        std::cerr << "Usage: keygenerator -h <HWID>  (generate key for HWID)\n";
        std::cerr << "       keygenerator -l           (show current device HWID)\n";
        return 1;
    }
    
    QString key = LicenseManager::generateAdminKey(hwid);
    
    std::cout << "\n============================================\n";
    std::cout << "AMONEY ADVANCE KYC - ACTIVATION KEY\n";
    std::cout << "============================================\n";
    std::cout << "HWID: " << hwid.toStdString() << "\n";
    std::cout << "Key:  " << key.toStdString() << "\n";
    std::cout << "============================================\n\n";
    std::cout << "Give this key to the user. It will ONLY work on the device with HWID: " << hwid.toStdString() << "\n";
    std::cout << "If they share the app to another computer, it will require a NEW key for that HWID.\n";
    
    return 0;
}