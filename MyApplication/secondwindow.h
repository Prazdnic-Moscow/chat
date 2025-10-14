#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QDialog>
QT_BEGIN_NAMESPACE
namespace Ui
{
    class secondwindow;
}
QT_END_NAMESPACE

class secondwindow : public QDialog
{
    Q_OBJECT

public:
    explicit secondwindow(QStackedWidget *stackedWidget = nullptr, QWidget *parent = nullptr);
    ~secondwindow();

private:
    Ui::secondwindow *ui;
    QStackedWidget *stackedWidget;
};

#endif
