#include <QtCore/QString>
#include <QMessageBox>
#include "logindialog.h"
#include "ui_logindialog.h"
#include "agent.h"
#include "log.h"



LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    connect(ui->pushButtonLogin, SIGNAL(clicked()), this, SLOT(onLoginClicked()));
    connect(ui->pushButtonExit, SIGNAL(clicked()), this, SLOT(onExitClicked()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::onLoginClicked()
{
    QString ip = ui->lineEditIp->text();
    int port = ui->lineEditPort->text().toInt();
    QString user=ui->lineEditUser->text();
    QString passwd = ui->lineEditPassword->text();

    osa_sockaddr_t serverAddr;
    osa_sockaddr_set(&serverAddr, ip.toLatin1().data(), port);

    if (!sysAgent->socket && sysAgent->openSocket() != OSA_ERR_OK)
    {
        GUI_LogError("Failed to open socket!\n");
        return;
    }

    if (sysAgent->connectToServer(&serverAddr) != OSA_ERR_OK)
    {
        GUI_LogError("Failed to connect to server !\n");

        QMessageBox::critical(NULL, "critical", "Faield to connect to server!",
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }

    if (sysAgent->loginSystem(user.toLatin1().data(), passwd.toLatin1().data()) != OSA_ERR_OK)
    {
        GUI_LogError("Failed to login system!\n");
        sysAgent->setLoginState(OSA_FALSE);

        QMessageBox::critical(NULL, "critical", "Faield to login system!",
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        return;
    }
    else
    {
        this->close();
        sysAgent->setLoginState(OSA_TRUE);
    }
}

void LoginDialog::onExitClicked()
{
    close();
}
