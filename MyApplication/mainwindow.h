#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showCaptcha();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_radioButton_clicked();

private:
    Ui::MainWindow *ui;
    QString getMachineUUID();
    void checkMachineIdentification();
};
#endif // MAINWINDOW_H
