#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>  // Добавьте этот include

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QStackedWidget *stackedWidget = nullptr, QWidget *parent = nullptr);  // Измените конструктор
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_radioButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;  // Добавьте этот член
    void showCaptcha();
    QString getMachineUUID();
    void checkMachineIdentification();
};

#endif // MAINWINDOW_H
