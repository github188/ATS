#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "ui_logindialog.h"
#include "agent.h"
#include "cJSON.h"
#include "log.h"
#include "devconnectdialog.h"
#include "device.h"
#include "configdialog.h"
#include "aboutdialog.h"


using namespace ATS;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sdkMng.loadAllSDK();

    reportReceiver = new QUdpSocket(this);
    reportReceiver->bind(QHostAddress::Any, 3000);

    ui->actionOpen_O->setDisabled(false);
    ui->actionClose_C->setDisabled(true);
    ui->treeWidget->setSortingEnabled(true);
    ui->textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->pushButtonStartTest->setDisabled(true);

    connect(ui->actionOpen_O, SIGNAL(triggered()), this, SLOT(onOpenClicked()));
    connect(ui->actionClose_C, SIGNAL(triggered()), this, SLOT(onCloseClicked()));
    connect(ui->actionExit_E, SIGNAL(triggered()), this, SLOT(onExitClicked()));
    connect(ui->treeWidget, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(onTreeViewItemPressed(QTreeWidgetItem*,int)));
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTreeViewRightClicked(QPoint)));
    connect(ui->actionConfig_C, SIGNAL(triggered()), this, SLOT(onConfigClicked()));
    connect(ui->actionAbout_A, SIGNAL(triggered()), this, SLOT(onAboutClicked()));
    connect(reportReceiver, SIGNAL(readyRead()), this, SLOT(onReportSockHasData()));
    connect(ui->textBrowser, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTextBrowserRightClicked(QPoint)));
    connect(ui->pushButtonStartTest, SIGNAL(clicked()), this, SLOT(onStartTestClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenClicked()
{
    LoginDialog loginDlg(this);

    loginDlg.exec();

    if (sysAgent->getLoginState() == OSA_TRUE)
    {
        ui->actionOpen_O->setDisabled(true);
        ui->actionClose_C->setDisabled(false);

        sysAgent->getDevices();

        updateDevices();
    }
    else
    {
        ui->actionOpen_O->setDisabled(false);
        ui->actionClose_C->setDisabled(true);

        ui->treeWidget->clear();
    }
}

void MainWindow::onCloseClicked()
{
    if (sysAgent->getLoginState() == OSA_FALSE)
    {
        return;
    }

    if (sysAgent->exitSystem() != OSA_ERR_OK)
    {
        return;
    }

    sysAgent->closeSocket();

    Device::removeAllDev();

    ui->actionOpen_O->setDisabled(false);
    ui->actionClose_C->setDisabled(true);
    ui->treeWidget->clear();
}

void MainWindow::onExitClicked()
{
    if (sysAgent->getLoginState() == OSA_TRUE)
    {
        sysAgent->exitSystem();
    }

    sysAgent->closeSocket();

    Device::removeAllDev();

    ui->treeWidget->clear();

    close();
}

void MainWindow::updateDevices()
{
    QTreeWidgetItem  *devRoot = new QTreeWidgetItem(ui->treeWidget, QStringList(QString("Devices")));

    list <Device *>::iterator itr;
    Device *dev = NULL;
    QString devName;

    for (itr=Device::devList.begin(); itr!=Device::devList.end(); itr++)
    {
        dev = *itr;
        devName =dev->getDevName().c_str();
        QTreeWidgetItem *devItem = new QTreeWidgetItem(devRoot, QStringList(devName));
        devRoot->addChild(devItem);
    }

    ui->treeWidget->expandAll();
}


void MainWindow::onTreeViewItemPressed(QTreeWidgetItem *item, int col)
{
    updateLoginState();
}


void MainWindow::onTreeViewRightClicked(QPoint pos)
{
    QMenu *menu=new QMenu(ui->treeWidget);

    QAction *actionLoginDev = new QAction(tr("Login Device"),this);
    QAction *actionExitDev = new QAction(tr("Logout Device"), this);
    QAction *actionTestDev = new QAction(tr("Test Device"),this);
    QAction *actionShowDev = new QAction(tr("Show Info"),this);
    QAction *actionRefresh = new QAction(tr("Refresh"), this);

    actionLoginDev->setData(QVariant("LoginDev"));
    actionExitDev->setData(QVariant("ExitDev"));
    actionTestDev->setData(QVariant("TestDev"));
    actionShowDev->setData(QVariant("ShowDev"));
    actionRefresh->setData(QVariant("Refresh"));

    menu->addAction(actionLoginDev);
    menu->addAction(actionExitDev);
    menu->addAction(actionTestDev);
    menu->addAction(actionShowDev);
    menu->addAction(actionRefresh);

    if (sysAgent->getLoginState() == OSA_FALSE)
    {
        actionLoginDev->setDisabled(true);
        actionExitDev->setDisabled(false);
        actionTestDev->setDisabled(true);
        actionShowDev->setDisabled(true);
    }

    QTreeWidgetItem *currItem = ui->treeWidget->currentItem();
    if(!currItem)
    {
        return;
    }

    Device *currDev = Device::findDev(currItem->text(0).toStdString());
    if (!currDev)
    {
        return;
    }

    if (currDev->getLoginState() == OSA_FALSE)
    {
        actionLoginDev->setDisabled(false);
        actionExitDev->setDisabled(true);
        actionTestDev->setDisabled(true);
    }
    else
    {
        actionTestDev->setDisabled(false);
        actionLoginDev->setDisabled(true);
        actionExitDev->setDisabled(false);
    }

    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(onTreeViewMenuShowed(QAction*)));

    menu->exec(QCursor::pos());
}

void MainWindow::onTreeViewMenuShowed(QAction *action)
{
    QTreeWidgetItem *currItem = ui->treeWidget->currentItem();
    if (!currItem)
    {
        return;
    }

    Device *currDev = Device::findDev(currItem->text(0).toStdString());
    if (!currDev)
    {
        GUI_LogError("Device not found!\n");
        return;
    }

    QVariant act(action->data());

    if (act == QVariant("LoginDev"))
    {
        DevConnectDialog dlg;

        DeviceInfo devInfo = currDev->getDevInfo();

        dlg.setDevName(QString::fromLocal8Bit(currDev->getDevName().c_str()));
        dlg.setDevIp(QString::fromLocal8Bit(devInfo.ipAddr.c_str()));

        dlg.exec();

        updateLoginState();
    }
    else if(act == QVariant("ExitDev"))
    {
        currDev->setLoginState(OSA_FALSE);
        ui->pushButtonStartTest->setDisabled(true);
    }
    else if (act == QVariant("TestDev"))
    {
        sysAgent->testDevice(currDev->getDevName().c_str());
    }
    else if (act == QVariant("ShowDev"))
    {
        QString info;
        DeviceInfo devInfo = currDev->getDevInfo();

        info +="Name: " + QString::fromLocal8Bit(currDev->getDevName().c_str()) + "\n";
        info +="IP: " + QString::fromLocal8Bit(devInfo.ipAddr.c_str()) + "\n";

        QMessageBox::information(this, "Device Info", info);
    }
    else if (act == QVariant("Refresh"))
    {
        ui->treeWidget->clear();
        sysAgent->getDevices();
        updateDevices();
    }
}

void MainWindow::onConfigClicked()
{
    ConfigDialog dlg;
    dlg.exec();
}


void MainWindow::onAboutClicked()
{
    AboutDialog dlg;
    dlg.exec();
}


void MainWindow::onReportSockHasData()
{
    QByteArray datagram;
    ui->textBrowser->setTextColor(QColor(255,0,0));

    while (reportReceiver->hasPendingDatagrams())
    {
        datagram.resize(reportReceiver->pendingDatagramSize());
        reportReceiver->readDatagram(datagram.data(), datagram.size());

        ui->textBrowser->append(QString(datagram.data()));
    }
}

void MainWindow::onTextBrowserRightClicked(QPoint pos)
{
    QMenu *menu=new QMenu(ui->textBrowser);

    QAction *actionClear = new QAction(tr("Clear"),this);
    QAction *actionSelectAll = new QAction(tr("Select All"), this);

    actionClear->setData(QVariant("Clear"));
    actionSelectAll->setData(QVariant("SelectAll"));

    menu->addAction(actionClear);
    menu->addAction(actionSelectAll);

    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(onTextBrowserMenuClicked(QAction*)));

    menu->exec(QCursor::pos());
}


void MainWindow::onTextBrowserMenuClicked(QAction *action)
{
    QVariant act(action->data());

    if (act == QVariant("Clear"))
    {
        ui->textBrowser->clear();
    }
}

void MainWindow::onStartTestClicked()
{
    QTreeWidgetItem *currItem = ui->treeWidget->currentItem();
    if (!currItem)
    {
        return;
    }

    Device *currDev = Device::findDev(currItem->text(0).toStdString());
    if (!currDev)
    {
        GUI_LogError("Device not found!\n");
        return;
    }
    sysAgent->testDevice(currDev->getDevName().c_str());
}

void MainWindow::updateLoginState()
{
    QTreeWidgetItem *currItem = ui->treeWidget->currentItem();
    if (!currItem)
    {
        return;
    }

    Device *currDev = Device::findDev(currItem->text(0).toStdString());
    if (!currDev)
    {
        GUI_LogError("Device not found!\n");
        return;
    }


    if (currDev->getLoginState() == OSA_FALSE)
    {
        ui->pushButtonStartTest->setDisabled(true);
    }
    else
    {
        ui->pushButtonStartTest->setDisabled(false);
    }
}
