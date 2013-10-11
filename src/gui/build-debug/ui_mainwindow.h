/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_O;
    QAction *actionClose_C;
    QAction *actionExit_E;
    QAction *actionConfig_C;
    QAction *actionAbout_A;
    QWidget *centralWidget;
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout_2;
    QGraphicsView *graphicsView;
    QSpacerItem *horizontalSpacer;
    QTextBrowser *textBrowser;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonStartTest;
    QPushButton *pushButtonStopTest;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuHelp_H;
    QMenu *menuTool_T;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(832, 662);
        MainWindow->setContextMenuPolicy(Qt::CustomContextMenu);
        actionOpen_O = new QAction(MainWindow);
        actionOpen_O->setObjectName(QString::fromUtf8("actionOpen_O"));
        actionClose_C = new QAction(MainWindow);
        actionClose_C->setObjectName(QString::fromUtf8("actionClose_C"));
        actionExit_E = new QAction(MainWindow);
        actionExit_E->setObjectName(QString::fromUtf8("actionExit_E"));
        actionConfig_C = new QAction(MainWindow);
        actionConfig_C->setObjectName(QString::fromUtf8("actionConfig_C"));
        actionAbout_A = new QAction(MainWindow);
        actionAbout_A->setObjectName(QString::fromUtf8("actionAbout_A"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        formLayout = new QFormLayout(centralWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(600, 450));
        graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout_2->addWidget(graphicsView);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setMinimumSize(QSize(256, 100));
        textBrowser->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout_2->addWidget(textBrowser);


        formLayout->setLayout(0, QFormLayout::LabelRole, verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeWidget = new QTreeWidget(centralWidget);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout->addWidget(treeWidget);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_2);

        pushButtonStartTest = new QPushButton(centralWidget);
        pushButtonStartTest->setObjectName(QString::fromUtf8("pushButtonStartTest"));

        verticalLayout->addWidget(pushButtonStartTest);

        pushButtonStopTest = new QPushButton(centralWidget);
        pushButtonStopTest->setObjectName(QString::fromUtf8("pushButtonStopTest"));

        verticalLayout->addWidget(pushButtonStopTest);


        formLayout->setLayout(0, QFormLayout::FieldRole, verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 832, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuHelp_H = new QMenu(menuBar);
        menuHelp_H->setObjectName(QString::fromUtf8("menuHelp_H"));
        menuTool_T = new QMenu(menuBar);
        menuTool_T->setObjectName(QString::fromUtf8("menuTool_T"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuTool_T->menuAction());
        menuBar->addAction(menuHelp_H->menuAction());
        menu->addAction(actionOpen_O);
        menu->addAction(actionClose_C);
        menu->addSeparator();
        menu->addAction(actionExit_E);
        menuHelp_H->addAction(actionAbout_A);
        menuTool_T->addAction(actionConfig_C);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionOpen_O->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200(&O)", 0, QApplication::UnicodeUTF8));
        actionClose_C->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255(&C)", 0, QApplication::UnicodeUTF8));
        actionExit_E->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272(&E)", 0, QApplication::UnicodeUTF8));
        actionConfig_C->setText(QApplication::translate("MainWindow", "\351\200\211\351\241\271(&P)", 0, QApplication::UnicodeUTF8));
        actionAbout_A->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216(&A)", 0, QApplication::UnicodeUTF8));
        textBrowser->setDocumentTitle(QApplication::translate("MainWindow", "Report", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "\350\256\276\345\244\207\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        pushButtonStartTest->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        pushButtonStopTest->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "\350\277\236\346\216\245(&C)", 0, QApplication::UnicodeUTF8));
        menuHelp_H->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251(&H)", 0, QApplication::UnicodeUTF8));
        menuTool_T->setTitle(QApplication::translate("MainWindow", "\345\267\245\345\205\267(&T)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
