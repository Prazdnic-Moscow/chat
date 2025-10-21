#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include <QInputDialog>
#include <QRandomGenerator>
#include "secondwindow.h"
#include "QJsonObject"
#include "QJsonDocument"
#include "QtNetwork/QNetworkAccessManager"
#include "QtNetwork/QNetworkReply"
#include <QtNetwork/QNetworkRequest>
#include <QDebug>
#include <QTimer>
#include "commonutils.h"

MainWindow::MainWindow(QStackedWidget *stackedWidget, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    stackedWidget(stackedWidget)
{
    ui->setupUi(this);
    ui->radioButton->setChecked(false);
    MainWindow::on_radioButton_clicked();

    loadingOverlay = new QWidget(this);
    loadingOverlay->setStyleSheet("background-color: rgba(0, 0, 0, 180);");
    loadingOverlay->setGeometry(this->rect());
    loadingOverlay->setFocusPolicy(Qt::StrongFocus);
    loadingOverlay->setAttribute(Qt::WA_NoSystemBackground, true);
    loadingOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    loadingOverlay->setWindowModality(Qt::ApplicationModal);
    loadingOverlay->setGeometry(0, 0, 420, 760);
    loadingOverlay->show();

    QLabel *loadingLabel = new QLabel("🔄 Проверка устройства...", loadingOverlay);
    loadingLabel->setStyleSheet("color: white; font-size: 16px; font-weight: bold;");
    loadingLabel->setAlignment(Qt::AlignCenter);
    loadingLabel->setGeometry(0, 0, loadingOverlay->width(), loadingOverlay->height());
    loadingLabel->show();
    overlayActive = true;


    QString machineUUID = CommonUtils::getMachineUUID().trimmed().toUpper();

    if (machineUUID == "unknown_uuid")
    {
        loadingOverlay->close();
        QMessageBox::warning(this, "Ошибка", "Не удалось определить идентификатор устройства!");
        QTimer::singleShot(100, qApp, &QCoreApplication::quit);
        return;
    }

    // готовим JSON
    QJsonObject json;
    json["machine_id"] = machineUUID;
    QByteArray data = QJsonDocument(json).toJson();

    // создаём менеджер и делаем POST
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("http://localhost:6666/identification"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [this, reply]()
    {
        if (loadingOverlay)
        {
            loadingOverlay->hide();
            loadingOverlay->deleteLater();
            loadingOverlay = nullptr;
            overlayActive = false;
            disconnect(this, &MainWindow::resizeEvent, nullptr, nullptr);
        }

        if (reply->error() == QNetworkReply::NoError)
        {
            QMessageBox::information(this, "Успех", "Ваша машина есть в базе");
        }
        else
        {
            if (reply->error() == QNetworkReply::ConnectionRefusedError ||
                reply->error() == QNetworkReply::TimeoutError ||
                reply->error() == QNetworkReply::HostNotFoundError)
            {
                QMessageBox::warning(this, "Ошибка сети", "Не удалось подключиться к серверу");
                QTimer::singleShot(100, qApp, &QCoreApplication::quit);
            }
            else
            {
                QMessageBox::critical(this, "Ошибка", "Вашей машины нет в базе\n");
                QTimer::singleShot(100, qApp, &QCoreApplication::quit);
            }
        }
        reply->deleteLater();
    });
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    // проверяем, что overlay существует и видим
    if (loadingOverlay && overlayActive && loadingOverlay->isVisible())
    {
        qDebug() << "зашли";
        loadingOverlay->setGeometry(this->rect());
        if (auto label = loadingOverlay->findChild<QLabel*>())
        {
            label->setGeometry(0, 0, loadingOverlay->width(), loadingOverlay->height());
        }
    }
}



void MainWindow::on_pushButton_clicked()
{
    QString machineUUID = CommonUtils::getMachineUUID();

    // Проверяем UUID перед регистрацией
    if (machineUUID == "unknown_uuid")
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось определить устройство!");
        return;
    }
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

    // Проверка телефона (11 цифр, начинается с 7 или 8)
    QRegularExpression phoneRegex("^[78][0-9]{10}$");
    if (!phoneRegex.match(phone).hasMatch())
    {
        QMessageBox::warning(this, "Предупреждение",
                             "Телефон должен:\n"
                             "- Состоять из 11 цифр\n"
                             "- Начинаться с 7 или 8\n"
                             "- Содержать только цифры");
        count = count + 1;
        if (CommonUtils::showCaptcha(this, count))
        {
            count = 0;
            return;
        }
        return;
    }

    // Проверка email (должен содержать @ и точку, минимальная длина 6 символов)
    if (email.length() < 6 || !email.contains('@') || !email.contains('.') || email.indexOf('@') < 1)
    {
        QMessageBox::warning(this, "Предупреждение", "Email должен быть в формате example@domain.com и содержать не менее 6 символов");
        count = count + 1;
        if (CommonUtils::showCaptcha(this, count))
        {
            count = 0;
            return;
        }
        return;
    }

    // Проверка адреса (минимум 5 символов)
        if (adress.length() < 5)
    {
        QMessageBox::warning(this, "Предупреждение", "Адрес должен содержать не менее 5 символов");
            count = count + 1;
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
    json["machine_id"] = machineUUID;
    // Преобразуем в JSON документ и в QByteArray
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    // Создаём менеджер и запрос
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("http://localhost:6666/register"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Отправляем POST-запрос
    QNetworkReply *reply = manager->post(request, data);

    connect(reply, &QNetworkReply::finished, [reply, this, login, machineUUID]()
    {
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray response = reply->readAll();
            QMessageBox::information(this, "Успех", "Регистрация прошла успешно!");
            secondwindow *secondWin = qobject_cast<secondwindow*>(stackedWidget->widget(2));
            if (secondWin)
            {
                secondWin->setUsername(login);
                secondWin->setMachineId(machineUUID);
            }
            stackedWidget->setCurrentIndex(2);
        }
        else
        {
            if (reply->error() == QNetworkReply::ConnectionRefusedError ||
                reply->error() == QNetworkReply::TimeoutError ||
                reply->error() == QNetworkReply::HostNotFoundError)
            {
                // Сетевые ошибки
                QMessageBox::warning(this, "Ошибка сети", "Не удалось подключиться к серверу");
            }
            else
            {
                QMessageBox::warning(this, "Ошибка", "Ошибка при регистрации:\n Пользователь с таким логином уже существует");
            }
        }
        reply->deleteLater();
    });
}

void MainWindow::on_pushButton_2_clicked()  // Кнопка "Войти"
{
    if (stackedWidget)
    {
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


