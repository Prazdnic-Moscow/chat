#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
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

    protected:
        void resizeEvent(QResizeEvent *event) override;

    private:
        Ui::MainWindow *ui;
        QStackedWidget *stackedWidget;
        void checkMachineIdentification();
        QWidget *loadingOverlay = nullptr;
        bool overlayActive = false;
        int count = 0;
        QString machineUUID;
};

#endif
