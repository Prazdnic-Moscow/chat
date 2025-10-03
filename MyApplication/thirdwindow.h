#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H

#include <QDialog>
#include <QWidget>
#include "mainwindow.h"
class MainWindow;

namespace Ui {
class thirdwindow;
}

class thirdwindow : public QDialog
{
    Q_OBJECT

public:
    explicit thirdwindow(MainWindow *mainWindow = nullptr, QWidget *parent = nullptr);
    ~thirdwindow();

private slots:

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::thirdwindow *ui;
    MainWindow *mainWindowPtr;
    void showCaptcha_3();
};

#endif // THIRDWINDOW_H
