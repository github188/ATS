#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QtNetwork/QUdpSocket>
#include "osa.h"
#include "sdkmanger.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateDevices();

signals:


private slots:
    void onOpenClicked();
    void onCloseClicked();
    void onExitClicked();
    void onTreeViewItemPressed(QTreeWidgetItem *item , int col);
    void onTreeViewRightClicked(QPoint pos);
    void onTreeViewMenuShowed(QAction *action);
    void onConfigClicked();
    void onAboutClicked();
    void onReportSockHasData();
    void onTextBrowserRightClicked(QPoint pos);
    void onTextBrowserMenuClicked(QAction *action);
    void onStartTestClicked();

private:
    void updateLoginState();


private:
    Ui::MainWindow  *ui;
    QUdpSocket *reportReceiver;
    ATS::SDKManger  sdkMng;
};

#endif // MAINWINDOW_H
