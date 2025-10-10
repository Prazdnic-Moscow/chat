#include "commonutils.h"
CommonUtils::CommonUtils(QObject *parent) : QObject(parent) {}

bool CommonUtils::showCaptcha(QWidget *parent, int &attemptCount)
{
    if (attemptCount == 3)
    {
        showCaptchaDialog(parent);
        attemptCount = 0;
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
        showCaptchaDialog(parent); // повторяем до успеха
    }
    else
    {
        QMessageBox::information(parent, "Успех", "Капча пройдена!");
    }
}

QString CommonUtils::getDarkTheme(const QString &windowClass)
{
    return QString(R"(
        %1 {
            background-image: url("../../raduga_dark.jpg");
            background-repeat: no-repeat;
            background-position: center;
            background-color: transparent;
            border: 2px solid gray;
            border-radius: 5px;
        }
        %1 QPushButton {
            background-color: rgba(80, 80, 80, 220);
            border-radius: 8px;
            border: 1px solid #cccccc;
            color: white;
        }
        %1 QLabel {
            color: white;
            background-color: rgba(80, 80, 80, 220);
            border: 1px solid #cccccc;
            border-radius: 7px;
        }
        %1 QLineEdit {
            background-color: rgba(80, 80, 80, 220);
            color: white;
            border: 1px solid #cccccc;
            border-radius: 7px;
        }
        %1 QRadioButton {
            color: white;
            border: 1px solid #cccccc;
            background-color: rgba(80, 80, 80, 220);
            border-radius: 7px;
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
            background-image: url("../../raduga.jpg");
            background-repeat: no-repeat;
            background-position: center;
            background-color: transparent;
            border: 2px solid gray;
            border-radius: 5px;
        }
        %1 QPushButton {
            background-color: rgba(255, 105, 180, 220);
            border-radius: 8px;
            border: 1px solid #444444;
            color: black;
        }
        %1 QLabel {
            color: black;
            background-color: rgba(255, 105, 180, 220);
            border-radius: 7px;
            border: 1px solid #444444;
        }
        %1 QLineEdit {
            background-color: rgba(255, 105, 180, 220);
            color: black;
            border: 1px solid #444444;
            border-radius: 7px;
        }
        %1 QRadioButton {
            color: black;
            background-color: rgba(255, 105, 180, 220);
            border: 1px solid #444444;
            border-radius: 7px;
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
