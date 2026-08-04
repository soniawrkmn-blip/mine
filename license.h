#ifndef LICENSE_H
#define LICENSE_H

#include <QString>
#include <QJsonObject>

class LicenseManager {
public:
    struct ActivationResult {
        bool success = false;
        QString message;
        QString hwid;
    };
    
    static QString getHWID();
    static QString getAppDataPath();
    static bool isActivated();
    static ActivationResult activate(const QString& key);
    static void deactivate();
    static QString getActivatedHWID();
    static QString generateAdminKey(const QString& hwid);
    static bool validateKey(const QString& key, const QString& hwid);

    // Create a machine activation request file for support containing the current HWID
    // Returns the full path to the generated request file or an empty string on error
    static QString createActivationRequest();
    
private:
    static const QString ADMIN_SECRET;
    static const QString ACTIVATION_FILE;
    static QString loadActivatedHWID();
    static bool saveActivatedHWID(const QString& hwid);
};

#endif // LICENSE_H
