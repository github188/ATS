/********************************************************************************
** Form generated from reading UI file 'devconnectdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVCONNECTDIALOG_H
#define UI_DEVCONNECTDIALOG_H

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

class Ui_DevConnectDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEditUser;
    QLineEdit *lineEditPassword;
    QPushButton *pushButtonLogin;
    QPushButton *pushButtonExit;
    QLabel *label_3;
    QLineEdit *lineEditDevName;
    QLabel *label_4;
    QLineEdit *lineEditIp;

    void setupUi(QDialog *DevConnectDialog)
    {
        if (DevConnectDialog->objectName().isEmpty())
            DevConnectDialog->setObjectName(QString::fromUtf8("DevConnectDialog"));
        DevConnectDialog->resize(400, 300);
        label = new QLabel(DevConnectDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(64, 120, 24, 16));
        label_2 = new QLabel(DevConnectDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(64, 148, 48, 16));
        lineEditUser = new QLineEdit(DevConnectDialog);
        lineEditUser->setObjectName(QString::fromUtf8("lineEditUser"));
        lineEditUser->setGeometry(QRect(120, 120, 133, 20));
        lineEditPassword = new QLineEdit(DevConnectDialog);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));
        lineEditPassword->setGeometry(QRect(120, 148, 133, 20));
        lineEditPassword->setMaxLength(16);
        lineEditPassword->setEchoMode(QLineEdit::Password);
        pushButtonLogin = new QPushButton(DevConnectDialog);
        pushButtonLogin->setObjectName(QString::fromUtf8("pushButtonLogin"));
        pushButtonLogin->setGeometry(QRect(90, 210, 80, 24));
        pushButtonExit = new QPushButton(DevConnectDialog);
        pushButtonExit->setObjectName(QString::fromUtf8("pushButtonExit"));
        pushButtonExit->setGeometry(QRect(200, 210, 80, 24));
        label_3 = new QLabel(DevConnectDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(64, 64, 36, 16));
        lineEditDevName = new QLineEdit(DevConnectDialog);
        lineEditDevName->setObjectName(QString::fromUtf8("lineEditDevName"));
        lineEditDevName->setGeometry(QRect(120, 64, 133, 20));
        lineEditDevName->setReadOnly(true);
        label_4 = new QLabel(DevConnectDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(64, 92, 16, 16));
        lineEditIp = new QLineEdit(DevConnectDialog);
        lineEditIp->setObjectName(QString::fromUtf8("lineEditIp"));
        lineEditIp->setGeometry(QRect(120, 92, 133, 20));
        lineEditIp->setReadOnly(true);

        retranslateUi(DevConnectDialog);

        QMetaObject::connectSlotsByName(DevConnectDialog);
    } // setupUi

    void retranslateUi(QDialog *DevConnectDialog)
    {
        DevConnectDialog->setWindowTitle(QApplication::translate("DevConnectDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DevConnectDialog", "User", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DevConnectDialog", "Password", 0, QApplication::UnicodeUTF8));
        lineEditUser->setText(QApplication::translate("DevConnectDialog", "admin", 0, QApplication::UnicodeUTF8));
        lineEditPassword->setText(QString());
        pushButtonLogin->setText(QApplication::translate("DevConnectDialog", "Login", 0, QApplication::UnicodeUTF8));
        pushButtonExit->setText(QApplication::translate("DevConnectDialog", "Exit", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("DevConnectDialog", "Device", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("DevConnectDialog", "IP", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
class DevConnectDialog: public Ui_DevConnectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVCONNECTDIALOG_H
