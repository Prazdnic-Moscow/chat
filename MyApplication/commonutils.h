#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <QObject>
#include <QInputDialog>
#include <QRandomGenerator>
#include <QMessageBox>

class CommonUtils : public QObject
{
    Q_OBJECT

    public:
        explicit CommonUtils(QObject *parent = nullptr);

        static QString getMachineUUID();
        static void checkMachineIdentificationAsync(QWidget *parent, std::function<void(bool)> callback);
        static bool showCaptcha(QWidget *parent, int &attemptCount);
        static QString getDarkTheme(const QString &windowClass);
        static QString getLightTheme(const QString &windowClass);

    private:
        static void showCaptchaDialog(QWidget *parent);
};

#endif
