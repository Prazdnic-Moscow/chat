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
#include "commonutils.h"

int count =0;

MainWindow::MainWindow(QStackedWidget *stackedWidget, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stackedWidget(stackedWidget)  // Правильная инициализация
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

        // Используем общую капчу
        if (CommonUtils::showCaptcha(this, count))
        {
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

void MainWindow::on_pushButton_2_clicked()  // Кнопка "Войти"
{
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(1);  // Переключаем на окно входа
    }
}

void MainWindow::on_radioButton_clicked()
{
    if (ui->radioButton->isChecked())
    {
        this->setStyleSheet(CommonUtils::getDarkTheme("#MainWindow"));
    }
    else
    {
        this->setStyleSheet(CommonUtils::getLightTheme("#MainWindow"));
    }
}
