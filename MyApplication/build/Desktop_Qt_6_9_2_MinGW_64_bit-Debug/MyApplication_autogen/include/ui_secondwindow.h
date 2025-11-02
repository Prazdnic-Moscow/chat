/********************************************************************************
** Form generated from reading UI file 'secondwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECONDWINDOW_H
#define UI_SECONDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_secondwindow
{
public:
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *savedchange;
    QPushButton *createFile;
    QPushButton *openfile;
    QTextEdit *textfile;
    QRadioButton *radioButton3;

    void setupUi(QDialog *secondwindow)
    {
        if (secondwindow->objectName().isEmpty())
            secondwindow->setObjectName("secondwindow");
        secondwindow->resize(894, 847);
        secondwindow->setMinimumSize(QSize(420, 760));
        secondwindow->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(secondwindow);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        groupBox = new QGroupBox(secondwindow);
        groupBox->setObjectName("groupBox");
        groupBox->setMaximumSize(QSize(700, 16777215));
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(15);
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: none;\n"
"}"));
        groupBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        groupBox->setFlat(false);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        savedchange = new QPushButton(groupBox);
        savedchange->setObjectName("savedchange");
        savedchange->setFont(font);

        horizontalLayout->addWidget(savedchange);

        createFile = new QPushButton(groupBox);
        createFile->setObjectName("createFile");
        createFile->setFont(font);

        horizontalLayout->addWidget(createFile);

        openfile = new QPushButton(groupBox);
        openfile->setObjectName("openfile");
        openfile->setFont(font);

        horizontalLayout->addWidget(openfile);


        verticalLayout_2->addLayout(horizontalLayout);

        textfile = new QTextEdit(groupBox);
        textfile->setObjectName("textfile");

        verticalLayout_2->addWidget(textfile);

        radioButton3 = new QRadioButton(groupBox);
        radioButton3->setObjectName("radioButton3");
        radioButton3->setMaximumSize(QSize(150, 16777215));
        radioButton3->setFont(font);

        verticalLayout_2->addWidget(radioButton3);


        horizontalLayout_2->addWidget(groupBox);


        retranslateUi(secondwindow);

        QMetaObject::connectSlotsByName(secondwindow);
    } // setupUi

    void retranslateUi(QDialog *secondwindow)
    {
        secondwindow->setWindowTitle(QCoreApplication::translate("secondwindow", "Dialog", nullptr));
        groupBox->setTitle(QString());
        savedchange->setText(QCoreApplication::translate("secondwindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        createFile->setText(QCoreApplication::translate("secondwindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        openfile->setText(QCoreApplication::translate("secondwindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        radioButton3->setText(QCoreApplication::translate("secondwindow", "\320\241\320\274\320\265\320\275\320\270\321\202\321\214 \321\202\320\265\320\274\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class secondwindow: public Ui_secondwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDWINDOW_H
