#include "secondwindow.h"
#include "ui_secondwindow.h"

secondwindow::secondwindow(QStackedWidget *stackedWidget, QWidget *parent):
    QDialog(parent),
    ui(new Ui::secondwindow),
    stackedWidget(stackedWidget)
{
    ui->setupUi(this);
}

secondwindow::~secondwindow()
{
    delete ui;
}
