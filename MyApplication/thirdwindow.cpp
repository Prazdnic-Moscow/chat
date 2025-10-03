#include "thirdwindow.h"
#include "ui_thirdwindow.h"
#include "mainwindow.h"
#include <QInputDialog>
#include <QRandomGenerator>
#include "QMessageBox"
#include "secondwindow.h"
#include <iostream>
#include "QJsonObject"
#include "QJsonDocument"
#include "QtNetwork/QNetworkAccessManager"
#include "QtNetwork/QNetworkReply"
#include <QtNetwork/QNetworkRequest>
#include <QProcess>
#include <QDebug>
#include <QTimer>
int count_3 = 0;
thirdwindow::thirdwindow(MainWindow *mainWindow, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::thirdwindow)
    , mainWindowPtr(mainWindow)  // Сохраняем указатель
{
    ui->setupUi(this);
    {

        ui->radioButton_2->setChecked(false);
        thirdwindow::on_radioButton_2_clicked();
        // QTimer::singleShot(0, this, &MainWindow::checkMachineIdentification);
    }
}

thirdwindow::~thirdwindow()
{
    delete ui;
}

void thirdwindow::on_pushButton_4_clicked()
{
    if (mainWindowPtr)
    {
        mainWindowPtr->show();
    }
    this->close();
}


void thirdwindow::on_pushButton_3_clicked()
{
    QString login = ui->login_enter->text();
    QString password = ui->password_enter->text();
    if (login.length() != 4 || password.length() != 6)
    {
        QMessageBox::warning(this, "Предупреждение", "Логин должен быть 4 символа а Пароль 6 символов");
        count_3 = count_3 + 1;

        if (count_3 == 3)
        {
            showCaptcha_3();
            count_3 = 0;
            return;
        }
        return;
    }
    // Создаём JSON объект
    QJsonObject json;
    json["username"] = login;
    json["password"] = password;
    // Преобразуем в JSON документ и в QByteArray
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    // Создаём менеджер и запрос
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("http://localhost:6666/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Отправляем POST-запрос
    QNetworkReply *reply = manager->post(request, data);

    // Обработка ответа
    connect(reply, &QNetworkReply::finished, [reply, this]()
    {

        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray response = reply->readAll();
            QMessageBox::information(this, "Успех", "Регистрация прошла успешно!");
            this->hide();
            secondwindow *window = new secondwindow;
            window->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
            window->show();
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Ошибка при регистрации:\n" + reply->errorString());
        }
        reply->deleteLater();
    });
}


void thirdwindow::showCaptcha_3()
{
    int number_1 = QRandomGenerator::global()->bounded(1, 10);
    int number_2 = QRandomGenerator::global()->bounded(1, 10);

    int captcha = number_1 + number_2;

    bool ok;
    QString question = QString("Решите пример: %1 + %2 = ?")
                           .arg(number_1)
                           .arg(number_2);

    QString text = QInputDialog::getText(this, "Капча",
                                         question,
                                         QLineEdit::Normal,
                                         "",
                                         &ok);

    if (!ok || text != QString::number(captcha))
    {
        QMessageBox::warning(this, "Ошибка", "Капча введена неверно!");
        showCaptcha_3(); // повторяем до успеха
    }
    else
    {
        QMessageBox::information(this, "Успех", "Капча пройдена!");
        count_3 = 0; // сбрасываем счётчик
    }
}


void thirdwindow::on_radioButton_2_clicked()
{
    if (ui->radioButton_2->isChecked())
    {
        // ТЁМНАЯ ТЕМА (когда кнопка нажата)
        QString darkTheme = R"(
            #thirdwindow {
                background-image: url("../../raduga_dark.jpg");
                background-repeat: no-repeat;
                background-position: center;
                background-color: transparent;
                border: 2px solid gray;
                border-radius: 5px;
            }
            #thirdwindow QPushButton {
                background-color: rgba(80, 80, 80, 220);
                border-radius: 8px;
                border: 1px solid #cccccc;
                color: white;
            }
            #thirdwindow QLabel {
                color: white;
                background-color: rgba(80, 80, 80, 220);
                border: 1px solid #cccccc;
                border-radius: 7px;
            }
            #thirdwindow QLineEdit {
                background-color: rgba(80, 80, 80, 220);
                color: white;
                border: 1px solid #cccccc;
                border-radius: 7px;
            }
            #thirdwindow QRadioButton {
                color: white;
                border: 1px solid #cccccc;
                background-color: rgba(80, 80, 80, 220);
                border-radius: 7px;
            }

            /* Стандартные стили для QMessageBox */
            #thirdwindow QMessageBox {
                background-color: #f0f0f0;
                color: #000000;
                font-family: "Segoe UI", Arial, sans-serif;
                font-size: 10pt;
            }

            #thirdwindow QMessageBox QLabel{
                color: black;
                background-color: #f0f0f0;
                border-radius: 0px;
                border: none;
            }

            #thirdwindow QMessageBox QPushButton {
                background-color: #e1e1e1;
                border-radius: 6px;
                color: #000000;
                border: 1px solid #444444;
                padding: 5px 15px;
                font-size: 10pt;
            }
            #thirdwindow QMessageBox QPushButton:hover {
                background-color: #d0d0d0;
            }
            #thirdwindow QMessageBox QPushButton:pressed {
                background-color: #c0c0c0;
            }
            #thirdwindow QMessageBox QLabel {
                color: #000000;
                background-color: transparent;
                font-size: 10pt;
            }


            /* Стандартные стили для QInputDialog */
            #thirdwindow QInputDialog {
                background-color: #f0f0f0;
                color: #000000;
                font-family: "Segoe UI", Arial, sans-serif;
                font-size: 10pt;
            }

            #thirdwindow QInputDialog QLabel {
                color: #000000;
                background-color: transparent;
                border: none;
                font-size: 10pt;
            }

            #thirdwindow QInputDialog QLineEdit {
                background-color: #ffffff;
                color: #000000;
                border: 1px solid #cccccc;
                border-radius: 4px;
                padding: 3px;
                font-size: 10pt;
            }

            #thirdwindow QInputDialog QPushButton {
                background-color: #e1e1e1;
                border-radius: 6px;
                color: #000000;
                border: 1px solid #444444;
                padding: 5px 15px;
                font-size: 10pt;
            }
            #thirdwindow QInputDialog QPushButton:hover {
                background-color: #d0d0d0;
            }
            #thirdwindow QInputDialog QPushButton:pressed {
                background-color: #c0c0c0;
            }

        )";
        this->setStyleSheet(darkTheme);
    }
    else
    {
        QString lightTheme = R"(
            #thirdwindow {
                background-image: url("../../raduga.jpg");
                background-repeat: no-repeat;
                background-position: center;
                background-color: transparent;
                border: 2px solid gray;
                border-radius: 5px;
            }
            #thirdwindow QPushButton {
                background-color: rgba(255, 105, 180, 220);
                border-radius: 8px;
                border: 1px solid #444444;
                color: black;
            }
            #thirdwindow QLabel {
                color: black;
                background-color: rgba(255, 105, 180, 220);
                border-radius: 7px;
                border: 1px solid #444444;
            }
            #thirdwindow QLineEdit {
                background-color: rgba(255, 105, 180, 220);
                color: black;
                border: 1px solid #444444;
                border-radius: 7px;
            }
            #thirdwindow QRadioButton {
                color: black;
                background-color: rgba(255, 105, 180, 220);
                border: 1px solid #444444;
                border-radius: 7px;
            }

            /* Стандартные стили для QMessageBox */
            #thirdwindow QMessageBox {
                background-color: #f0f0f0;
                color: #000000;
                font-family: "Segoe UI", Arial, sans-serif;
                font-size: 10pt;
            }

            #thirdwindow QMessageBox QLabel{
                color: black;
                background-color: #f0f0f0;
                border-radius: 0px;
                border: none;
            }

            #thirdwindow QMessageBox QPushButton {
                background-color: #e1e1e1;
                border-radius: 6px;
                color: #000000;
                border: 1px solid #444444;
                padding: 5px 15px;
                font-size: 10pt;
            }
            #thirdwindow QMessageBox QPushButton:hover {
                background-color: #d0d0d0;
            }
            #thirdwindow QMessageBox QPushButton:pressed {
                background-color: #c0c0c0;
            }
            #thirdwindow QMessageBox QLabel {
                color: #000000;
                background-color: transparent;
                font-size: 10pt;
            }

            /* Стандартные стили для QInputDialog */
            #thirdwindow QInputDialog {
                background-color: #f0f0f0;
                color: #000000;
                font-family: "Segoe UI", Arial, sans-serif;
                font-size: 10pt;
            }

            #thirdwindow QInputDialog QLabel {
                color: #000000;
                background-color: transparent;
                border: none;
                font-size: 10pt;
            }

            #thirdwindow QInputDialog QLineEdit {
                background-color: #ffffff;
                color: #000000;
                border: 1px solid #cccccc;
                border-radius: 4px;
                padding: 3px;
                font-size: 10pt;
            }

            #thirdwindow QInputDialog QPushButton {
                background-color: #e1e1e1;
                border-radius: 6px;
                color: #000000;
                border: 1px solid #444444;
                padding: 5px 15px;
                font-size: 10pt;
            }
            #thirdwindow QInputDialog QPushButton:hover {
                background-color: #d0d0d0;
            }
            #thirdwindow QInputDialog QPushButton:pressed {
                background-color: #c0c0c0;
            }

        )";
        this->setStyleSheet(lightTheme);
    }
}

