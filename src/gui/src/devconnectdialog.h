#ifndef DEVCONNECTDIALOG_H
#define DEVCONNECTDIALOG_H

#include <QDialog>
#include <QtCore/QString>

namespace Ui {
class DevConnectDialog;
}

class DevConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DevConnectDialog(QWidget *parent = 0);
    ~DevConnectDialog();

    void setDevName(const QString &name);
    void setDevIp(const QString &ip);

private slots:
    void onLoginClicked();
    void onExitClicked();

private:
    Ui::DevConnectDialog *ui;
};

#endif // DEVCONNECTDIALOG_H
