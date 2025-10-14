#include "commonutils.h"
#include <QProcess>
#include "QJsonObject"
#include "QJsonDocument"
#include "QtNetwork/QNetworkAccessManager"
#include "QtNetwork/QNetworkReply"
#include <QtNetwork/QNetworkRequest>
#include <QDebug>
#include <QTimer>
CommonUtils::CommonUtils(QObject *parent) : QObject(parent) {}

bool CommonUtils::showCaptcha(QWidget *parent, int &attemptCount)
{
    if (attemptCount == 3)
    {
        showCaptchaDialog(parent);
        return true;
    }
    return false;
}

void CommonUtils::showCaptchaDialog(QWidget *parent)
{
    int number_1 = QRandomGenerator::global()->bounded(1, 10);
    int number_2 = QRandomGenerator::global()->bounded(1, 10);
    int captcha = number_1 + number_2;
    bool ok;

    QString question = QString("Решите пример: %1 + %2 = ?").arg(number_1).arg(number_2);

    QString text = QInputDialog::getText(parent, "Капча", question, QLineEdit::Normal, "", &ok);

    if (!ok || text != QString::number(captcha))
    {
        QMessageBox::warning(parent, "Ошибка", "Капча введена неверно!");
        showCaptchaDialog(parent);
    }
    else
    {
        QMessageBox::information(parent, "Успех", "Капча пройдена!");
    }
}


QString CommonUtils::getMachineUUID()
{
#ifdef Q_OS_WIN
    QProcess process;
    // Запуск PowerShell и получение UUID
    process.start("powershell", QStringList()
                                    << "-Command"
                                    << "(Get-CimInstance Win32_ComputerSystemProduct).UUID");

    if (process.waitForFinished(3000))
    {
        QString output = QString::fromLocal8Bit(process.readAllStandardOutput()).trimmed();
        if (!output.isEmpty() && output.length() == 36 && output.contains('-'))
        {
            return output;
        }
    }
    else
    {
        qDebug() << "Timeout while getting UUID";
    }
#endif
    return "unknown_uuid";
}

QString CommonUtils::getDarkTheme(const QString &windowClass)
{
    return QString(R"(
        %1 {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1a1a1a, stop:0.5 #2d2d2d, stop:1 #1a1a1a);
            border: 2px solid gray;
            border-radius: 5px;
        }
        %1 QPushButton {
            background-color: rgba(80, 80, 80, 220);
            border-radius: 8px;
            border: 1px solid #cccccc;
            color: white;
        }

        %1 QLabel[objectName="catLabel"],
        %1 QLabel[objectName="catLabel2"] {
            background: transparent;
            border: none;
            image: url(../../cat1.png);
        }

        %1 QLabel {
            color: white;
            background-color: rgba(80, 80, 80, 220);
            border: 1px solid #cccccc;
            border-radius: 8px;
        }
        %1 QLineEdit {
            background-color: rgba(80, 80, 80, 220);
            color: white;
            border: 1px solid #cccccc;
            border-radius: 8px;
        }
        %1 QRadioButton {
            color: white;
            border: 1px solid #cccccc;
            background-color: rgba(80, 80, 80, 220);
            border-radius: 8px;
        }

        /* Стандартные стили для QMessageBox */
        %1 QMessageBox {
            background-color: #f0f0f0;
            color: #000000;
            font-family: "Segoe UI", Arial, sans-serif;
            font-size: 10pt;
        }
        %1 QMessageBox QLabel{
            color: black;
            background-color: #f0f0f0;
            border-radius: 0px;
            border: none;
        }
        %1 QMessageBox QPushButton {
            background-color: #e1e1e1;
            border-radius: 6px;
            color: #000000;
            border: 1px solid #444444;
            padding: 5px 15px;
            font-size: 10pt;
        }
        %1 QMessageBox QPushButton:hover {
            background-color: #d0d0d0;
        }
        %1 QMessageBox QPushButton:pressed {
            background-color: #c0c0c0;
        }
        %1 QMessageBox QLabel {
            color: #000000;
            background-color: transparent;
            font-size: 10pt;
        }

        /* Стандартные стили для QInputDialog */
        %1 QInputDialog {
            background-color: #f0f0f0;
            color: #000000;
            font-family: "Segoe UI", Arial, sans-serif;
            font-size: 10pt;
        }
        %1 QInputDialog QLabel {
            color: #000000;
            background-color: transparent;
            border: none;
            font-size: 10pt;
        }
        %1 QInputDialog QLineEdit {
            background-color: #ffffff;
            color: #000000;
            border: 1px solid #cccccc;
            border-radius: 4px;
            padding: 3px;
            font-size: 10pt;
        }
        %1 QInputDialog QPushButton {
            background-color: #e1e1e1;
            border-radius: 6px;
            color: #000000;
            border: 1px solid #444444;
            padding: 5px 15px;
            font-size: 10pt;
        }
        %1 QInputDialog QPushButton:hover {
            background-color: #d0d0d0;
        }
        %1 QInputDialog QPushButton:pressed {
            background-color: #c0c0c0;
        }
    )").arg(windowClass);
}

QString CommonUtils::getLightTheme(const QString &windowClass)
{
    return QString(R"(
        %1 {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0 #f8c8dc, stop:0.5 #f0a6ca, stop:1 #f8c8dc);
            border: 2px solid gray;
            border-radius: 5px;
        }
        %1 QPushButton {
            background-color: rgba(255, 105, 180, 220);
            border-radius: 8px;
            border: 1px solid #444444;
            color: black;
        }

        %1 QLabel[objectName="catLabel"],
        %1 QLabel[objectName="catLabel2"] {
            background: transparent;
            border: none;
            image: url(../../cat1.png);
        }

        %1 QLabel {
            color: black;
            background-color: rgba(255, 105, 180, 220);
            border-radius: 8px;
            border: 1px solid #444444;
        }
        %1 QLineEdit {
            background-color: rgba(255, 105, 180, 220);
            color: black;
            border: 1px solid #444444;
            border-radius: 8px;
        }
        %1 QRadioButton {
            color: black;
            background-color: rgba(255, 105, 180, 220);
            border: 1px solid #444444;
            border-radius: 8px;
        }

        /* Стандартные стили для QMessageBox */
        %1 QMessageBox {
            background-color: #f0f0f0;
            color: #000000;
            font-family: "Segoe UI", Arial, sans-serif;
            font-size: 10pt;
        }
        %1 QMessageBox QLabel{
            color: black;
            background-color: #f0f0f0;
            border-radius: 0px;
            border: none;
        }
        %1 QMessageBox QPushButton {
            background-color: #e1e1e1;
            border-radius: 6px;
            color: #000000;
            border: 1px solid #444444;
            padding: 5px 15px;
            font-size: 10pt;
        }
        %1 QMessageBox QPushButton:hover {
            background-color: #d0d0d0;
        }
        %1 QMessageBox QPushButton:pressed {
            background-color: #c0c0c0;
        }
        %1 QMessageBox QLabel {
            color: #000000;
            background-color: transparent;
            font-size: 10pt;
        }

        /* Стандартные стили для QInputDialog */
        %1 QInputDialog {
            background-color: #f0f0f0;
            color: #000000;
            font-family: "Segoe UI", Arial, sans-serif;
            font-size: 10pt;
        }
        %1 QInputDialog QLabel {
            color: #000000;
            background-color: transparent;
            border: none;
            font-size: 10pt;
        }
        %1 QInputDialog QLineEdit {
            background-color: #ffffff;
            color: #000000;
            border: 1px solid #cccccc;
            border-radius: 4px;
            padding: 3px;
            font-size: 10pt;
        }
        %1 QInputDialog QPushButton {
            background-color: #e1e1e1;
            border-radius: 6px;
            color: #000000;
            border: 1px solid #444444;
            padding: 5px 15px;
            font-size: 10pt;
        }
        %1 QInputDialog QPushButton:hover {
            background-color: #d0d0d0;
        }
        %1 QInputDialog QPushButton:pressed {
            background-color: #c0c0c0;
        }
    )").arg(windowClass);
}
