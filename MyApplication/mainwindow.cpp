#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include <QInputDialog>
#include <QRandomGenerator>
#include "secondwindow.h"
#include "thirdwindow.h"
#include <iostream>
#include "QJsonObject"
#include "QJsonDocument"
#include "QtNetwork/QNetworkAccessManager"
#include "QtNetwork/QNetworkReply"
#include <QtNetwork/QNetworkRequest>
#include <QProcess>
#include <QDebug>
#include <QTimer>
#include <QPixmap>

int count =0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    {
        ui->radioButton->setChecked(false);  // Исправил на radioButton (без подчеркивания)
        MainWindow::on_radioButton_clicked();
        //QTimer::singleShot(0, this, &MainWindow::checkMachineIdentification);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getMachineUUID()
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



void MainWindow::checkMachineIdentification()
{
    QString machineUUID = getMachineUUID();
    machineUUID = machineUUID.trimmed();
    machineUUID = machineUUID.toUpper();

    qDebug() << "Machine UUID:" << machineUUID;

    if (machineUUID == "unknown_uuid")
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось определить идентификатор устройства!");
        return;
    }

    // Создаём JSON объект для идентификации
    QJsonObject json;
    json["machine_id"] = machineUUID;

    // Преобразуем в JSON документ
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    // Создаём менеджер и запрос
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("http://localhost:6666/identification"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Отправляем POST-запрос
    QNetworkReply *reply = manager->post(request, data);

    // Обработка ответа
    connect(reply, &QNetworkReply::finished, [reply, this]()
    {

        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray response = reply->readAll();
            QMessageBox::information(this, "Успех", "Ваша машина есть в базе");
        }
        else
        {
            QMessageBox::critical(this, "Ошибка", "Вашей машины нет в Базе:\n" + reply->errorString());
            reply->deleteLater();
            this->close();
        }
    });
}

void MainWindow::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();
    QString phone = ui->phone->text();
    QString email = ui->email->text();
    QString adress = ui->adress->text();
    if (login.length() != 4 || password.length() != 6)
    {
        QMessageBox::warning(this, "Предупреждение", "Логин должен быть 4 символа а Пароль 6 символов");
        count = count + 1;

        if (count == 3)
        {
            showCaptcha();
            count = 0;
            return;
        }
        return;
    }
    // Создаём JSON объект
    QJsonObject json;
    json["username"] = login;
    json["password"] = password;
    json["email"] = email;
    json["phone"] = phone;
    json["adress"] = adress;
    // Преобразуем в JSON документ и в QByteArray
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    // Создаём менеджер и запрос
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("http://localhost:6666/register"));
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


void MainWindow::showCaptcha()
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
        showCaptcha(); // повторяем до успеха
    }
    else
    {
        QMessageBox::information(this, "Успех", "Капча пройдена!");
        count = 0; // сбрасываем счётчик
    }
}



void MainWindow::on_radioButton_clicked()
{
    if (ui->radioButton->isChecked())
    {
        // ТЁМНАЯ ТЕМА (когда кнопка нажата)
        QString darkTheme = R"(
            #MainWindow {
                background-image: url("../../raduga_dark.jpg");
                background-repeat: no-repeat;
                background-position: center;
                background-color: transparent;
                border: 2px solid gray;
                border-radius: 5px;
            }
            #MainWindow QPushButton {
                background-color: rgba(80, 80, 80, 220);
                border-radius: 8px;
                border: 1px solid #cccccc;
                color: white;
            }
            #MainWindow QLabel {
                color: white;
                background-color: rgba(80, 80, 80, 220);
                border: 1px solid #cccccc;
                border-radius: 7px;
            }
            #MainWindow QLineEdit {
                background-color: rgba(80, 80, 80, 220);
                color: white;
                border: 1px solid #cccccc;
                border-radius: 7px;
            }
            #MainWindow QRadioButton {
                color: white;
                border: 1px solid #cccccc;
                background-color: rgba(80, 80, 80, 220);
                border-radius: 7px;
            }

            /* Стандартные стили для QMessageBox */
            #MainWindow QMessageBox {
                background-color: #f0f0f0;
                color: #000000;
                font-family: "Segoe UI", Arial, sans-serif;
                font-size: 10pt;
            }

            #MainWindow QMessageBox QLabel{
                color: black;
                background-color: #f0f0f0;
                border-radius: 0px;
                border: none;
            }

            #MainWindow QMessageBox QPushButton {
                background-color: #e1e1e1;
                border-radius: 6px;
                color: #000000;
                border: 1px solid #444444;
                padding: 5px 15px;
                font-size: 10pt;
            }
            #MainWindow QMessageBox QPushButton:hover {
                background-color: #d0d0d0;
            }
            #MainWindow QMessageBox QPushButton:pressed {
                background-color: #c0c0c0;
            }
            #MainWindow QMessageBox QLabel {
                color: #000000;
                background-color: transparent;
                font-size: 10pt;
            }


            /* Стандартные стили для QInputDialog */
            #MainWindow QInputDialog {
                background-color: #f0f0f0;
                color: #000000;
                font-family: "Segoe UI", Arial, sans-serif;
                font-size: 10pt;
            }

            #MainWindow QInputDialog QLabel {
                color: #000000;
                background-color: transparent;
                border: none;
                font-size: 10pt;
            }

            #MainWindow QInputDialog QLineEdit {
                background-color: #ffffff;
                color: #000000;
                border: 1px solid #cccccc;
                border-radius: 4px;
                padding: 3px;
                font-size: 10pt;
            }

            #MainWindow QInputDialog QPushButton {
                background-color: #e1e1e1;
                border-radius: 6px;
                color: #000000;
                border: 1px solid #444444;
                padding: 5px 15px;
                font-size: 10pt;
            }
            #MainWindow QInputDialog QPushButton:hover {
                background-color: #d0d0d0;
            }
            #MainWindow QInputDialog QPushButton:pressed {
                background-color: #c0c0c0;
            }

        )";
        this->setStyleSheet(darkTheme);
    }
    else
    {
        QString lightTheme = R"(
            #MainWindow {
                background-image: url("../../raduga.jpg");
                background-repeat: no-repeat;
                background-position: center;
                background-color: transparent;
                border: 2px solid gray;
                border-radius: 5px;
            }
            #MainWindow QPushButton {
                background-color: rgba(255, 105, 180, 220);
                border-radius: 8px;
                border: 1px solid #444444;
                color: black;
            }
            #MainWindow QLabel {
                color: black;
                background-color: rgba(255, 105, 180, 220);
                border-radius: 7px;
                border: 1px solid #444444;
            }
            #MainWindow QLineEdit {
                background-color: rgba(255, 105, 180, 220);
                color: black;
                border: 1px solid #444444;
                border-radius: 7px;
            }
            #MainWindow QRadioButton {
                color: black;
                background-color: rgba(255, 105, 180, 220);
                border: 1px solid #444444;
                border-radius: 7px;
            }

            /* Стандартные стили для QMessageBox */
            #MainWindow QMessageBox {
                background-color: #f0f0f0;
                color: #000000;
                font-family: "Segoe UI", Arial, sans-serif;
                font-size: 10pt;
            }

            #MainWindow QMessageBox QLabel{
                color: black;
                background-color: #f0f0f0;
                border-radius: 0px;
                border: none;
            }

            #MainWindow QMessageBox QPushButton {
                background-color: #e1e1e1;
                border-radius: 6px;
                color: #000000;
                border: 1px solid #444444;
                padding: 5px 15px;
                font-size: 10pt;
            }
            #MainWindow QMessageBox QPushButton:hover {
                background-color: #d0d0d0;
            }
            #MainWindow QMessageBox QPushButton:pressed {
                background-color: #c0c0c0;
            }
            #MainWindow QMessageBox QLabel {
                color: #000000;
                background-color: transparent;
                font-size: 10pt;
            }

            /* Стандартные стили для QInputDialog */
            #MainWindow QInputDialog {
                background-color: #f0f0f0;
                color: #000000;
                font-family: "Segoe UI", Arial, sans-serif;
                font-size: 10pt;
            }

            #MainWindow QInputDialog QLabel {
                color: #000000;
                background-color: transparent;
                border: none;
                font-size: 10pt;
            }

            #MainWindow QInputDialog QLineEdit {
                background-color: #ffffff;
                color: #000000;
                border: 1px solid #cccccc;
                border-radius: 4px;
                padding: 3px;
                font-size: 10pt;
            }

            #MainWindow QInputDialog QPushButton {
                background-color: #e1e1e1;
                border-radius: 6px;
                color: #000000;
                border: 1px solid #444444;
                padding: 5px 15px;
                font-size: 10pt;
            }
            #MainWindow QInputDialog QPushButton:hover {
                background-color: #d0d0d0;
            }
            #MainWindow QInputDialog QPushButton:pressed {
                background-color: #c0c0c0;
            }

        )";
        this->setStyleSheet(lightTheme);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    this->hide();
    thirdwindow *window = new thirdwindow(this);
    window->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    window->show();
}

