#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "commonutils.h"
#include <QCryptographicHash>
#include <QFileInfo>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTimer>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFileDialog>

secondwindow::secondwindow(QStackedWidget *stackedWidget, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::secondwindow),
    stackedWidget(stackedWidget),
    networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    ui->radioButton3->setChecked(false);
    secondwindow::on_radioButton3_clicked();
}

secondwindow::~secondwindow()
{
    delete ui;
}

void secondwindow::on_radioButton3_clicked()
{
    if (ui->radioButton3->isChecked())
        this->setStyleSheet(CommonUtils::getDarkTheme("#secondwindow"));
    else
        this->setStyleSheet(CommonUtils::getLightTheme("#secondwindow"));
}

/* ============================
 *  СОХРАНЕНИЕ ФАЙЛА (шифрование)
 * ============================ */
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

    // Проверяем роль пользователя
    QJsonObject roleJson;
    roleJson["username"] = username;
    roleJson["machine_id"] = machineUUID;

    QNetworkRequest roleReq(QUrl("http://localhost:6666/checkrole"));
    roleReq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *roleReply = networkManager->post(roleReq, QJsonDocument(roleJson).toJson());

    connect(roleReply, &QNetworkReply::finished, [this, roleReply]()
            {
                if (roleReply->error() != QNetworkReply::NoError)
                {
                    QMessageBox::warning(this, "Ошибка сети", "Не удалось проверить права доступа.");
                    roleReply->deleteLater();
                    return;
                }

                // Роль разрешена, можно сохранять
                QFile file(currentFilePath);
                if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
                    roleReply->deleteLater();
                    return;
                }

                QString plainText = ui->textfile->toPlainText();
                QString encrypted = simpleEncryptDecrypt(plainText); // шифруем перед записью
                file.write(encrypted.toUtf8());
                file.close();

                // Вычисляем хеш нового содержимого
                QString newHash = calculateFileHash(currentFilePath);

                // Отправляем обновление хеша на сервер
                QJsonObject hashJson;
                hashJson["file_path"] = currentFilePath;
                hashJson["new_hash"] = newHash;
                hashJson["username"] = username;
                hashJson["action"] = "update";

                QNetworkRequest hashReq(QUrl("http://localhost:6666/updatefilehash"));
                hashReq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

                QNetworkReply *hashReply = networkManager->post(hashReq, QJsonDocument(hashJson).toJson());

                connect(hashReply, &QNetworkReply::finished, [this, hashReply, newHash]()
                        {
                            if (hashReply->error() == QNetworkReply::NoError)
                            {
                                currentFileHash = newHash;
                                QMessageBox::information(this, "Успех", "Файл зашифрован и успешно сохранен!");
                            }
                            else
                            {
                                QMessageBox::warning(this, "Ошибка", "Не удалось обновить хеш в базе данных.");
                            }
                            hashReply->deleteLater();
                        });

                roleReply->deleteLater();
            });
}

/* ============================
 *  ОТКРЫТИЕ ФАЙЛА (дешифрование)
 * ============================ */
void secondwindow::on_openfile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Выберите файл",
                                                    "C:/",
                                                    "Secret Files (*.secretextension);");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл: " + fileName);
        return;
    }

    QString encryptedContent = QString::fromUtf8(file.readAll());
    file.close();

    QString decryptedContent = simpleDecrypt(encryptedContent);
    if (decryptedContent.isEmpty() && !encryptedContent.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось расшифровать содержимое файла.");
        return;
    }

    // Проверка целостности через сервер
    QString fileHash = calculateFileHash(fileName);
    QJsonObject json;
    json["file_path"] = fileName;
    json["current_hash"] = fileHash;

    QNetworkRequest request(QUrl("http://localhost:6666/verifyfilehash"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(json).toJson());

    connect(reply, &QNetworkReply::finished, [this, reply, fileName, decryptedContent]()
            {
                if (reply->error() != QNetworkReply::NoError)
                {
                    QMessageBox::warning(this, "Ошибка сети", "Ошибка при проверке целостности файла.");
                    reply->deleteLater();
                    return;
                }

                int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
                if (statusCode == 200)
                {
                    ui->textfile->setPlainText(decryptedContent);
                    currentFilePath = fileName;
                    QMessageBox::information(this, "Успех", "Файл успешно расшифрован и открыт.");
                }
                else
                {
                    QMessageBox::critical(this, "Нарушение целостности",
                                          "Обнаружено изменение файла! Возможна несанкционированная модификация.");
                    QTimer::singleShot(10000, this, [this]()
                                       {
                                           QMessageBox::information(this, "Блокировка", "Программа разблокирована.");
                                       });
                }

                reply->deleteLater();
            });
}

/* ============================
 *  СОЗДАНИЕ НОВОГО ФАЙЛА
 * ============================ */
void secondwindow::on_createFile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Создать новый файл",
                                                    "C:/",
                                                    "Secret Files (*.secretextension)");

    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".secretextension", Qt::CaseInsensitive))
        fileName += ".secretextension";

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось создать файл: " + fileName);
        return;
    }

    QString encrypted = simpleEncryptDecrypt(""); // создаём зашифрованный пустой файл
    file.write(encrypted.toUtf8());
    file.close();

    currentFilePath = fileName;
    ui->textfile->clear();

    QString initialHash = calculateFileHash(fileName);

    QJsonObject json;
    json["file_path"] = fileName;
    json["new_hash"] = initialHash;
    json["username"] = username;
    json["action"] = "create";

    QNetworkRequest request(QUrl("http://localhost:6666/updatefilehash"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(json).toJson());

    connect(reply, &QNetworkReply::finished, [this, reply, fileName]()
            {
                if (reply->error() == QNetworkReply::NoError)
                {
                    QMessageBox::information(this, "Успех", "Файл создан и защищен!");
                }
                else
                {
                    QMessageBox::warning(this, "Ошибка", "Не удалось зарегистрировать файл в БД.");
                }
                reply->deleteLater();
            });

    QMessageBox::information(this, "Файл создан", "Вы можете начать редактирование нового файла.");
}

/* ============================
 *  ХЕШИРОВАНИЕ
 * ============================ */
QString secondwindow::calculateFileHash(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return QString();

    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(&file);
    file.close();

    return hash.result().toHex();
}

/* ============================
 *  ШИФРОВАНИЕ / ДЕШИФРОВКА
 * ============================ */
QString secondwindow::simpleEncryptDecrypt(const QString &text)
{
    QByteArray data = text.toUtf8();
    for (int i = 0; i < data.size(); ++i)
        data[i] = data[i] ^ 0xAA;
    return QString::fromUtf8(data.toBase64());
}

QString secondwindow::simpleDecrypt(const QString &encrypted)
{
    QByteArray data = QByteArray::fromBase64(encrypted.toUtf8());
    for (int i = 0; i < data.size(); ++i)
        data[i] = data[i] ^ 0xAA;
    return QString::fromUtf8(data);
}

/* ============================
 *  ЗАКРЫТИЕ ОКНА
 * ============================ */
void secondwindow::closeEvent(QCloseEvent *event)
{
    event->accept(); // просто закрываем, ничего не переименовываем
}
