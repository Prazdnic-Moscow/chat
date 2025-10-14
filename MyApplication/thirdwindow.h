#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H

#include <QDialog>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class thirdwindow;
}
QT_END_NAMESPACE

class thirdwindow : public QDialog
{
    Q_OBJECT

    public:
        explicit thirdwindow(QStackedWidget *stackedWidget = nullptr, QWidget *parent = nullptr);  // Измените конструктор
        ~thirdwindow();

    private slots:
        void on_pushButton_4_clicked();
        void on_pushButton_3_clicked();
        void on_radioButton_2_clicked();

    private:
        Ui::thirdwindow *ui;
        QStackedWidget *stackedWidget;
        void showCaptcha_3();
        int count_3 = 0;
};

#endif
