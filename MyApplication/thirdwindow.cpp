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
#include "commonutils.h"

thirdwindow::thirdwindow(QStackedWidget *stackedWidget, QWidget *parent):
    QDialog(parent),
    ui(new Ui::thirdwindow),
    stackedWidget(stackedWidget)
{
    ui->setupUi(this);
    {
        ui->radioButton_2->setChecked(false);
        thirdwindow::on_radioButton_2_clicked();
    }
}

thirdwindow::~thirdwindow()
{
    delete ui;
}

void thirdwindow::on_pushButton_4_clicked()  // Кнопка "Назад"
{
    if (stackedWidget)
    {
        stackedWidget->setCurrentIndex(0);  // Возврат к регистрации
    }
}

void thirdwindow::on_radioButton_2_clicked()
{
    if (ui->radioButton_2->isChecked())
    {
        this->setStyleSheet(CommonUtils::getDarkTheme("#thirdwindow"));
    }
    else
    {
        this->setStyleSheet(CommonUtils::getLightTheme("#thirdwindow"));
    }
}


void thirdwindow::on_pushButton_3_clicked()
{
     QString machineUUID = CommonUtils::getMachineUUID();
    // Проверяем UUID перед регистрацией
    if (machineUUID == "unknown_uuid")
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось определить устройство!");
        return;
    }

    QString login = ui->login_enter->text();
    QString password = ui->password_enter->text();
    if (login.length() != 4 || password.length() != 6)
    {
        QMessageBox::warning(this, "Предупреждение", "Логин должен быть 4 символа а Пароль 6 символов");
        count_3 = count_3 + 1;

        // Используем общую капчу
        if (CommonUtils::showCaptcha(this, count_3))
        {
            count_3 = 0;
            return;
        }
        return;

    }
    // Создаём JSON объект
    QJsonObject json;
    json["username"] = login;
    json["password"] = password;
    json["machine_id"] = machineUUID;
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
            stackedWidget->setCurrentIndex(2);
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Ошибка при регистрации:\n Неверный Логин или Пароль");
            count_3 = count_3 + 1;
            if (CommonUtils::showCaptcha(this, count_3))
            {
                count_3 = 0;
            }
        }
        reply->deleteLater();
    });
}



