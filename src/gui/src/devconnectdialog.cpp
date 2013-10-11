#include "devconnectdialog.h"
#include "ui_devconnectdialog.h"
#include "device.h"
#include <QMessageBox>

using namespace ATS;

DevConnectDialog::DevConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DevConnectDialog)
{
    ui->setupUi(this);

    connect(ui->pushButtonLogin, SIGNAL(clicked()), this, SLOT(onLoginClicked()));
    connect(ui->pushButtonExit, SIGNAL(clicked()), this, SLOT(onExitClicked()));
}

DevConnectDialog::~DevConnectDialog()
{
    delete ui;
}

void DevConnectDialog::setDevName(const QString &name)
{
    ui->lineEditDevName->setText(name);
}


void DevConnectDialog::setDevIp(const QString &ip)
{
    ui->lineEditIp->setText(ip);
}


void DevConnectDialog::onLoginClicked()
{
    QString user = ui->lineEditUser->text();
    QString passwd = ui->lineEditPassword->text();

    QString devName = ui->lineEditDevName->text();

    Device *dev = Device::findDev(devName.toStdString());
    if (!dev)
    {
        return;
    }

    if (dev->loginDev(user.toStdString(), passwd.toStdString()) == OSA_ERR_OK)
    {
        dev->setLoginState(OSA_TRUE);
        close();
    }
    else
    {
        dev->setLoginState(OSA_FALSE);
    }


    if (dev->getLoginState() == OSA_FALSE)
    {
        QMessageBox::critical(NULL, "critical", "Faield to login device!",
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

void DevConnectDialog::onExitClicked()
{
    close();
}
