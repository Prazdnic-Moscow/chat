#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QNetworkAccessManager>
#include <QDialog>
#include <QFileDialog>
#include "QJsonObject"
#include "QJsonDocument"
#include "QtNetwork/QNetworkAccessManager"
#include "QtNetwork/QNetworkReply"
#include <QtNetwork/QNetworkRequest>
#include <QDebug>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui
{
    class secondwindow;
}
QT_END_NAMESPACE

class secondwindow : public QDialog
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    explicit secondwindow(QStackedWidget *stackedWidget = nullptr, QWidget *parent = nullptr);
    ~secondwindow();
    void setUsername(const QString &usernamefromMain){this->username = usernamefromMain; }
    void setMachineId(const QString &machineUUIDfromMain){this->machineUUID = machineUUIDfromMain;}

private slots:
    void on_savedchange_clicked();
    void on_openfile_clicked();
    void on_radioButton3_clicked();
    void on_createFile_clicked();

private:
    Ui::secondwindow *ui;
    QStackedWidget *stackedWidget;
    QString currentFilePath;
    QString username;
    QString machineUUID;
    QNetworkAccessManager *networkManager;
    QString currentFileHash;
    QString calculateFileHash(const QString &filePath);
    QString getFileExtension(const QString &filePath);
    QString simpleEncryptDecrypt(const QString &text);
    QString simpleDecrypt(const QString &encrypted);
};
#endif
