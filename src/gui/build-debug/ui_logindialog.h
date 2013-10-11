/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEditIp;
    QLineEdit *lineEditPort;
    QLineEdit *lineEditUser;
    QLineEdit *lineEditPassword;
    QPushButton *pushButtonLogin;
    QPushButton *pushButtonExit;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(400, 300);
        label = new QLabel(LoginDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(52, 52, 16, 16));
        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(52, 108, 24, 16));
        label_3 = new QLabel(LoginDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(52, 136, 48, 16));
        label_4 = new QLabel(LoginDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(52, 80, 24, 16));
        lineEditIp = new QLineEdit(LoginDialog);
        lineEditIp->setObjectName(QString::fromUtf8("lineEditIp"));
        lineEditIp->setGeometry(QRect(110, 52, 133, 20));
        lineEditPort = new QLineEdit(LoginDialog);
        lineEditPort->setObjectName(QString::fromUtf8("lineEditPort"));
        lineEditPort->setGeometry(QRect(110, 80, 133, 20));
        lineEditUser = new QLineEdit(LoginDialog);
        lineEditUser->setObjectName(QString::fromUtf8("lineEditUser"));
        lineEditUser->setGeometry(QRect(110, 108, 133, 20));
        lineEditPassword = new QLineEdit(LoginDialog);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));
        lineEditPassword->setGeometry(QRect(110, 136, 133, 20));
        lineEditPassword->setEchoMode(QLineEdit::Password);
        pushButtonLogin = new QPushButton(LoginDialog);
        pushButtonLogin->setObjectName(QString::fromUtf8("pushButtonLogin"));
        pushButtonLogin->setGeometry(QRect(80, 210, 75, 23));
        pushButtonExit = new QPushButton(LoginDialog);
        pushButtonExit->setObjectName(QString::fromUtf8("pushButtonExit"));
        pushButtonExit->setGeometry(QRect(192, 210, 75, 23));

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("LoginDialog", "IP", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("LoginDialog", "User", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("LoginDialog", "Password", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("LoginDialog", "Port", 0, QApplication::UnicodeUTF8));
        lineEditIp->setText(QApplication::translate("LoginDialog", "127.0.0.1", 0, QApplication::UnicodeUTF8));
        lineEditPort->setText(QApplication::translate("LoginDialog", "2000", 0, QApplication::UnicodeUTF8));
        lineEditUser->setText(QApplication::translate("LoginDialog", "admin", 0, QApplication::UnicodeUTF8));
        lineEditPassword->setText(QApplication::translate("LoginDialog", "admin", 0, QApplication::UnicodeUTF8));
        pushButtonLogin->setText(QApplication::translate("LoginDialog", "Login", 0, QApplication::UnicodeUTF8));
        pushButtonExit->setText(QApplication::translate("LoginDialog", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
