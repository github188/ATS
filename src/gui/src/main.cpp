#include "mainwindow.h"
#include <QApplication>
#include "agent.h"
#include "osa.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 1
    sysAgent = new ATS::Agent();
    sysAgent->initAgentIOCH();

    MainWindow w;
    w.show();

    a.exec();

    delete sysAgent;

#endif
    return 0;
}
