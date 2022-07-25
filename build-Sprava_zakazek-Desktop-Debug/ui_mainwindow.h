/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionU_ivatel;
    QAction *actionZak_zky;
    QAction *actionPodle_id;
    QAction *actionPodle_sla_v_kresu;
    QAction *actionSeznam_z_vit;
    QAction *actionSmazat_historii;
    QAction *actionZm_nit_heslo;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QMenuBar *menuBar;
    QMenu *menuZobrazen;
    QMenu *menuHledat;
    QMenu *menuObnovit;
    QMenu *menuPokro_il;
    QMenu *menuDal;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionU_ivatel = new QAction(MainWindow);
        actionU_ivatel->setObjectName(QString::fromUtf8("actionU_ivatel"));
        actionU_ivatel->setCheckable(true);
        actionZak_zky = new QAction(MainWindow);
        actionZak_zky->setObjectName(QString::fromUtf8("actionZak_zky"));
        actionZak_zky->setCheckable(true);
        actionZak_zky->setChecked(true);
        actionPodle_id = new QAction(MainWindow);
        actionPodle_id->setObjectName(QString::fromUtf8("actionPodle_id"));
        actionPodle_id->setCheckable(true);
        actionPodle_id->setChecked(true);
        actionPodle_sla_v_kresu = new QAction(MainWindow);
        actionPodle_sla_v_kresu->setObjectName(QString::fromUtf8("actionPodle_sla_v_kresu"));
        actionPodle_sla_v_kresu->setCheckable(true);
        actionSeznam_z_vit = new QAction(MainWindow);
        actionSeznam_z_vit->setObjectName(QString::fromUtf8("actionSeznam_z_vit"));
        actionSmazat_historii = new QAction(MainWindow);
        actionSmazat_historii->setObjectName(QString::fromUtf8("actionSmazat_historii"));
        actionZm_nit_heslo = new QAction(MainWindow);
        actionZm_nit_heslo->setObjectName(QString::fromUtf8("actionZm_nit_heslo"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setFocusPolicy(Qt::NoFocus);
        tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout->addWidget(tableView);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        menuZobrazen = new QMenu(menuBar);
        menuZobrazen->setObjectName(QString::fromUtf8("menuZobrazen"));
        menuHledat = new QMenu(menuBar);
        menuHledat->setObjectName(QString::fromUtf8("menuHledat"));
        menuObnovit = new QMenu(menuBar);
        menuObnovit->setObjectName(QString::fromUtf8("menuObnovit"));
        menuObnovit->setMouseTracking(false);
        menuObnovit->setTearOffEnabled(false);
        menuPokro_il = new QMenu(menuBar);
        menuPokro_il->setObjectName(QString::fromUtf8("menuPokro_il"));
        menuDal = new QMenu(menuBar);
        menuDal->setObjectName(QString::fromUtf8("menuDal"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuZobrazen->menuAction());
        menuBar->addAction(menuPokro_il->menuAction());
        menuBar->addAction(menuDal->menuAction());
        menuBar->addAction(menuHledat->menuAction());
        menuBar->addAction(menuObnovit->menuAction());
        menuZobrazen->addAction(actionU_ivatel);
        menuZobrazen->addAction(actionZak_zky);
        menuPokro_il->addAction(actionPodle_id);
        menuPokro_il->addAction(actionPodle_sla_v_kresu);
        menuDal->addAction(actionSeznam_z_vit);
        menuDal->addAction(actionSmazat_historii);
        menuDal->addAction(actionZm_nit_heslo);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionU_ivatel->setText(QApplication::translate("MainWindow", "Users", nullptr));
        actionZak_zky->setText(QApplication::translate("MainWindow", "Orders", nullptr));
        actionPodle_id->setText(QApplication::translate("MainWindow", "By user", nullptr));
        actionPodle_sla_v_kresu->setText(QApplication::translate("MainWindow", "By batch", nullptr));
        actionSeznam_z_vit->setText(QApplication::translate("MainWindow", "Threads list", nullptr));
        actionSmazat_historii->setText(QApplication::translate("MainWindow", "Delete history", nullptr));
        actionZm_nit_heslo->setText(QApplication::translate("MainWindow", "Change password", nullptr));
        menuZobrazen->setTitle(QApplication::translate("MainWindow", "Window", nullptr));
        menuHledat->setTitle(QApplication::translate("MainWindow", "Search", nullptr));
        menuObnovit->setTitle(QApplication::translate("MainWindow", "Update", nullptr));
        menuPokro_il->setTitle(QApplication::translate("MainWindow", "Order mode", nullptr));
        menuDal->setTitle(QApplication::translate("MainWindow", "Other", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
