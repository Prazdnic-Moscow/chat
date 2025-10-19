#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "commonutils.h"

secondwindow::secondwindow(QStackedWidget *stackedWidget, QWidget *parent):
    QDialog(parent),
    ui(new Ui::secondwindow),
    stackedWidget(stackedWidget),
    networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    {
        ui->radioButton3->setChecked(false);
        secondwindow::on_radioButton3_clicked();
    }
}

secondwindow::~secondwindow()
{
    delete ui;
}

void secondwindow::on_radioButton3_clicked()
{
    if (ui->radioButton3->isChecked())
    {
        this->setStyleSheet(CommonUtils::getDarkTheme("#secondwindow"));
    }
    else
    {
        this->setStyleSheet(CommonUtils::getLightTheme("#secondwindow"));
    }
}

void secondwindow::on_savedchange_clicked()
{
    if (currentFilePath.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Нет открытого файла для сохранения.");
        return;
    }

    if (username.isEmpty() || machineUUID.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Информация о пользователе не найдена.");
        return;
    }
    // Подготавливаем JSON для проверки роли
    QJsonObject json;
    json["username"] = username;
    json["machine_id"] = machineUUID;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    // Отправляем запрос на проверку роли
    QNetworkRequest request(QUrl("http://localhost:6666/checkrole"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, data);


    connect(reply, &QNetworkReply::finished, [this, reply]()
    {
        // Проверяем тип ошибки
        if (reply->error() != QNetworkReply::NoError)
        {
            // Сетевые ошибки
            if (reply->error() == QNetworkReply::ConnectionRefusedError ||
                reply->error() == QNetworkReply::TimeoutError ||
                reply->error() == QNetworkReply::HostNotFoundError)
            {
                QMessageBox::warning(this, "Ошибка сети", "Не удалось подключиться к серверу");
            }
            else
            {
                QMessageBox::warning(this, "Ошибка","У вас нет прав для сохранения изменений.");
            }
            reply->deleteLater();
            return;
        }
        QFile file(currentFilePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << ui->textfile->toPlainText();
            file.close();
            QMessageBox::information(this, "Успех", "Изменения сохранены!");
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");
        }
        reply->deleteLater();
    });
}


void secondwindow::on_openfile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", "C:/", "Text Files (*.txt)");

    if (!fileName.isEmpty())
    {
        currentFilePath = fileName; // Сохраняем путь к файлу
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            QString content = in.readAll();
            ui->textfile->setPlainText(content);
            file.close();
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл: " + fileName);
        }
    }
}
