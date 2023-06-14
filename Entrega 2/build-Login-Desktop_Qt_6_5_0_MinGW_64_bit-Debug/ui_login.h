/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QGridLayout *gridLayout;
    QLineEdit *username_lineEdit;
    QLabel *username_label;
    QLineEdit *password_lineEdit;
    QLabel *password_label;
    QPushButton *submit_pusButton;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(521, 128);
        gridLayout = new QGridLayout(Login);
        gridLayout->setObjectName("gridLayout");
        username_lineEdit = new QLineEdit(Login);
        username_lineEdit->setObjectName("username_lineEdit");

        gridLayout->addWidget(username_lineEdit, 0, 1, 1, 2);

        username_label = new QLabel(Login);
        username_label->setObjectName("username_label");

        gridLayout->addWidget(username_label, 0, 0, 1, 1);

        password_lineEdit = new QLineEdit(Login);
        password_lineEdit->setObjectName("password_lineEdit");
        password_lineEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(password_lineEdit, 1, 1, 1, 2);

        password_label = new QLabel(Login);
        password_label->setObjectName("password_label");

        gridLayout->addWidget(password_label, 1, 0, 1, 1);

        submit_pusButton = new QPushButton(Login);
        submit_pusButton->setObjectName("submit_pusButton");

        gridLayout->addWidget(submit_pusButton, 2, 2, 1, 1);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Login", nullptr));
        username_label->setText(QCoreApplication::translate("Login", "Username", nullptr));
        password_label->setText(QCoreApplication::translate("Login", "Password", nullptr));
        submit_pusButton->setText(QCoreApplication::translate("Login", "Submit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
