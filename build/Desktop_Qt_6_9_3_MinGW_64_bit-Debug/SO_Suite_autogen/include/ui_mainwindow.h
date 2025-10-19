/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabs;
    QWidget *tabPlan;
    QVBoxLayout *vboxLayout;
    QWidget *planContainer;
    QWidget *tabConc;
    QVBoxLayout *vboxLayout1;
    QWidget *concContainer;
    QWidget *tabMem;
    QVBoxLayout *vboxLayout2;
    QWidget *memContainer;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabs = new QTabWidget(centralwidget);
        tabs->setObjectName("tabs");
        tabs->setTabPosition(QTabWidget::North);
        tabPlan = new QWidget();
        tabPlan->setObjectName("tabPlan");
        vboxLayout = new QVBoxLayout(tabPlan);
        vboxLayout->setObjectName("vboxLayout");
        planContainer = new QWidget(tabPlan);
        planContainer->setObjectName("planContainer");

        vboxLayout->addWidget(planContainer);

        tabs->addTab(tabPlan, QString());
        tabConc = new QWidget();
        tabConc->setObjectName("tabConc");
        vboxLayout1 = new QVBoxLayout(tabConc);
        vboxLayout1->setObjectName("vboxLayout1");
        concContainer = new QWidget(tabConc);
        concContainer->setObjectName("concContainer");

        vboxLayout1->addWidget(concContainer);

        tabs->addTab(tabConc, QString());
        tabMem = new QWidget();
        tabMem->setObjectName("tabMem");
        vboxLayout2 = new QVBoxLayout(tabMem);
        vboxLayout2->setObjectName("vboxLayout2");
        memContainer = new QWidget(tabMem);
        memContainer->setObjectName("memContainer");

        vboxLayout2->addWidget(memContainer);

        tabs->addTab(tabMem, QString());

        verticalLayout->addWidget(tabs);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "SO Suite", nullptr));
        tabs->setTabText(tabs->indexOf(tabPlan), QCoreApplication::translate("MainWindow", "Planificaci\303\263n", nullptr));
        tabs->setTabText(tabs->indexOf(tabConc), QCoreApplication::translate("MainWindow", "Concurrencia", nullptr));
        tabs->setTabText(tabs->indexOf(tabMem), QCoreApplication::translate("MainWindow", "Memoria", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
