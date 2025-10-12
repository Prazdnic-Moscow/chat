#include "mainwindow.h"
#include "thirdwindow.h"
#include <QApplication>
#include <QStackedWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStackedWidget *stackedWidget = new QStackedWidget;

    MainWindow *mainWindow = new MainWindow(stackedWidget);
    thirdwindow *loginWindow = new thirdwindow(stackedWidget);

    // Добавляем окна в stacked widget
    stackedWidget->addWidget(mainWindow);  // индекс 0 - регистрация
    stackedWidget->addWidget(loginWindow); // индекс 1 - вход
    stackedWidget->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint |
                                  Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    stackedWidget->show();
    return a.exec();
}
