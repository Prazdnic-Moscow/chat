/********************************************************************************
** Form generated from reading UI file 'thirdwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THIRDWINDOW_H
#define UI_THIRDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_thirdwindow
{
public:
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QLabel *label_7;
    QVBoxLayout *verticalLayout;
    QLineEdit *login_enter;
    QLineEdit *password_enter;
    QSpacerItem *verticalSpacer;
    QLabel *catLabel2;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer_3;
    QRadioButton *radioButton_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *thirdwindow)
    {
        if (thirdwindow->objectName().isEmpty())
            thirdwindow->setObjectName("thirdwindow");
        thirdwindow->resize(400, 760);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(thirdwindow->sizePolicy().hasHeightForWidth());
        thirdwindow->setSizePolicy(sizePolicy);
        thirdwindow->setMinimumSize(QSize(400, 0));
        horizontalLayout_3 = new QHBoxLayout(thirdwindow);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        groupBox = new QGroupBox(thirdwindow);
        groupBox->setObjectName("groupBox");
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
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
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setMinimumSize(QSize(0, 30));
        label_6->setMaximumSize(QSize(16777215, 30));
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8(""));
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_6);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setMinimumSize(QSize(0, 30));
        label_7->setMaximumSize(QSize(16777215, 30));
        label_7->setFont(font);
        label_7->setStyleSheet(QString::fromUtf8(""));
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_7);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName("verticalLayout");
        login_enter = new QLineEdit(groupBox);
        login_enter->setObjectName("login_enter");
        login_enter->setMinimumSize(QSize(150, 0));
        login_enter->setMaximumSize(QSize(16777215, 30));
        login_enter->setFont(font);
        login_enter->setStyleSheet(QString::fromUtf8(""));
        login_enter->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(login_enter);

        password_enter = new QLineEdit(groupBox);
        password_enter->setObjectName("password_enter");
        password_enter->setMinimumSize(QSize(0, 0));
        password_enter->setMaximumSize(QSize(16777215, 30));
        password_enter->setFont(font);
        password_enter->setStyleSheet(QString::fromUtf8(""));
        password_enter->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(password_enter);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 99, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);

        catLabel2 = new QLabel(groupBox);
        catLabel2->setObjectName("catLabel2");
        catLabel2->setMinimumSize(QSize(350, 350));
        catLabel2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(catLabel2);

        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(0, 29));
        pushButton_3->setMaximumSize(QSize(16777215, 30));
        pushButton_3->setFont(font);
        pushButton_3->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_3->addWidget(pushButton_3);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setFont(font);

        horizontalLayout_2->addWidget(label_8);

        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setFont(font);

        horizontalLayout_2->addWidget(pushButton_4);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalSpacer_3 = new QSpacerItem(20, 50, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);

        verticalLayout_4->addItem(verticalSpacer_3);


        verticalLayout_6->addLayout(verticalLayout_4);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setMaximumSize(QSize(150, 16777215));
        radioButton_2->setFont(font);
        radioButton_2->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_6->addWidget(radioButton_2);

        verticalSpacer_2 = new QSpacerItem(20, 21, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_6->addItem(verticalSpacer_2);


        horizontalLayout_3->addWidget(groupBox);


        retranslateUi(thirdwindow);

        QMetaObject::connectSlotsByName(thirdwindow);
    } // setupUi

    void retranslateUi(QDialog *thirdwindow)
    {
        thirdwindow->setWindowTitle(QCoreApplication::translate("thirdwindow", "Dialog", nullptr));
        groupBox->setTitle(QString());
        label_6->setText(QCoreApplication::translate("thirdwindow", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        label_7->setText(QCoreApplication::translate("thirdwindow", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        catLabel2->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("thirdwindow", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        label_8->setText(QCoreApplication::translate("thirdwindow", "\320\243 \320\262\320\260\321\201 \320\275\320\265\321\202\321\203 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\260?", nullptr));
        pushButton_4->setText(QCoreApplication::translate("thirdwindow", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        radioButton_2->setText(QCoreApplication::translate("thirdwindow", "\320\241\320\274\320\265\320\275\320\270\321\202\321\214 \321\202\320\265\320\274\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class thirdwindow: public Ui_thirdwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THIRDWINDOW_H
