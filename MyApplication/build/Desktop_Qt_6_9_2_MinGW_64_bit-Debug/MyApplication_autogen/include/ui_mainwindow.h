/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_5;
    QVBoxLayout *verticalLayout;
    QLineEdit *login;
    QLineEdit *password;
    QLineEdit *email;
    QLineEdit *phone;
    QLineEdit *adress;
    QLabel *catLabel;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer;
    QRadioButton *radioButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(400, 760);
        MainWindow->setMinimumSize(QSize(400, 0));
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setMinimumSize(QSize(0, 0));
        groupBox->setMaximumSize(QSize(700, 16777215));
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(16);
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"      border: none; \n"
"}"));
        groupBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(15);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setMinimumSize(QSize(0, 30));
        label->setMaximumSize(QSize(16777215, 30));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8(""));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(0, 30));
        label_2->setMaximumSize(QSize(16777215, 30));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8(""));
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setMinimumSize(QSize(0, 30));
        label_4->setMaximumSize(QSize(16777215, 30));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8(""));
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_4);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(0, 30));
        label_3->setMaximumSize(QSize(16777215, 30));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8(""));
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setMinimumSize(QSize(0, 30));
        label_5->setMaximumSize(QSize(16777215, 30));
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8(""));
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_5);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName("verticalLayout");
        login = new QLineEdit(groupBox);
        login->setObjectName("login");
        login->setMinimumSize(QSize(150, 0));
        login->setMaximumSize(QSize(16777215, 30));
        login->setFont(font);
        login->setStyleSheet(QString::fromUtf8(""));
        login->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(login);

        password = new QLineEdit(groupBox);
        password->setObjectName("password");
        password->setMinimumSize(QSize(0, 0));
        password->setMaximumSize(QSize(16777215, 30));
        password->setFont(font);
        password->setStyleSheet(QString::fromUtf8(""));
        password->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(password);

        email = new QLineEdit(groupBox);
        email->setObjectName("email");
        email->setMinimumSize(QSize(0, 0));
        email->setMaximumSize(QSize(16777215, 30));
        email->setFont(font);
        email->setStyleSheet(QString::fromUtf8(""));
        email->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(email);

        phone = new QLineEdit(groupBox);
        phone->setObjectName("phone");
        phone->setMinimumSize(QSize(0, 0));
        phone->setMaximumSize(QSize(16777215, 30));
        phone->setFont(font);
        phone->setStyleSheet(QString::fromUtf8(""));
        phone->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(phone);

        adress = new QLineEdit(groupBox);
        adress->setObjectName("adress");
        adress->setMinimumSize(QSize(0, 0));
        adress->setMaximumSize(QSize(16777215, 30));
        adress->setFont(font);
        adress->setStyleSheet(QString::fromUtf8(""));
        adress->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(adress);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        catLabel = new QLabel(groupBox);
        catLabel->setObjectName("catLabel");
        catLabel->setMinimumSize(QSize(350, 350));
        catLabel->setScaledContents(true);
        catLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        catLabel->setWordWrap(false);
        catLabel->setOpenExternalLinks(false);

        verticalLayout_3->addWidget(catLabel);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(0, 29));
        pushButton->setMaximumSize(QSize(16777215, 30));
        pushButton->setFont(font);
        pushButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_3->addWidget(pushButton);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setFont(font);

        horizontalLayout_2->addWidget(label_6);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setFont(font);

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);

        verticalLayout_4->addItem(verticalSpacer);


        verticalLayout_6->addLayout(verticalLayout_4);

        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName("radioButton");
        radioButton->setMaximumSize(QSize(150, 16777215));
        radioButton->setFont(font);
        radioButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_6->addWidget(radioButton);


        horizontalLayout_3->addWidget(groupBox);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 400, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\207\321\202\320\260", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", " \320\242\320\265\320\273\320\265\321\204\320\276\320\275 ", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\220\320\264\321\200\320\265\321\201", nullptr));
        catLabel->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\243\320\266\320\265 \320\265\321\201\321\202\321\214 \320\260\320\272\320\272\320\260\321\203\320\275\321\202?", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\274\320\265\320\275\320\270\321\202\321\214 \321\202\320\265\320\274\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
