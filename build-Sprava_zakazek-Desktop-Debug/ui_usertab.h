/********************************************************************************
** Form generated from reading UI file 'usertab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERTAB_H
#define UI_USERTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserTab
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLineEdit *item_edit;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *name_edit;
    QLabel *label_4;
    QLabel *item;
    QSpacerItem *verticalSpacer;
    QLineEdit *id_edit;
    QLabel *name;
    QLabel *id;
    QSpacerItem *verticalSpacer_3;
    QPushButton *edit;
    QPushButton *delete_2;
    QTableView *tableView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *UserTab)
    {
        if (UserTab->objectName().isEmpty())
            UserTab->setObjectName(QString::fromUtf8("UserTab"));
        UserTab->resize(800, 600);
        centralwidget = new QWidget(UserTab);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        item_edit = new QLineEdit(centralwidget);
        item_edit->setObjectName(QString::fromUtf8("item_edit"));
        item_edit->setEnabled(false);
        item_edit->setReadOnly(false);

        gridLayout->addWidget(item_edit, 8, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 5, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 5, 3, 1, 1);

        name_edit = new QLineEdit(centralwidget);
        name_edit->setObjectName(QString::fromUtf8("name_edit"));
        name_edit->setEnabled(false);
        name_edit->setReadOnly(false);

        gridLayout->addWidget(name_edit, 5, 2, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font;
        font.setPointSize(20);
        label_4->setFont(font);

        gridLayout->addWidget(label_4, 3, 0, 1, 4);

        item = new QLabel(centralwidget);
        item->setObjectName(QString::fromUtf8("item"));
        QFont font1;
        font1.setPointSize(10);
        item->setFont(font1);

        gridLayout->addWidget(item, 8, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 9, 0, 1, 1);

        id_edit = new QLineEdit(centralwidget);
        id_edit->setObjectName(QString::fromUtf8("id_edit"));
        id_edit->setEnabled(false);
        id_edit->setReadOnly(false);

        gridLayout->addWidget(id_edit, 7, 2, 1, 1);

        name = new QLabel(centralwidget);
        name->setObjectName(QString::fromUtf8("name"));
        name->setFont(font1);

        gridLayout->addWidget(name, 5, 0, 1, 1);

        id = new QLabel(centralwidget);
        id->setObjectName(QString::fromUtf8("id"));
        id->setFont(font1);

        gridLayout->addWidget(id, 7, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer_3, 4, 0, 1, 1);

        edit = new QPushButton(centralwidget);
        edit->setObjectName(QString::fromUtf8("edit"));

        gridLayout->addWidget(edit, 10, 0, 1, 1);

        delete_2 = new QPushButton(centralwidget);
        delete_2->setObjectName(QString::fromUtf8("delete_2"));

        gridLayout->addWidget(delete_2, 10, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout->addWidget(tableView);

        horizontalLayout->setStretch(1, 2);
        UserTab->setCentralWidget(centralwidget);
        menubar = new QMenuBar(UserTab);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        UserTab->setMenuBar(menubar);
        statusbar = new QStatusBar(UserTab);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        UserTab->setStatusBar(statusbar);

        retranslateUi(UserTab);

        QMetaObject::connectSlotsByName(UserTab);
    } // setupUi

    void retranslateUi(QMainWindow *UserTab)
    {
        UserTab->setWindowTitle(QApplication::translate("UserTab", "User card", nullptr));
        label_4->setText(QApplication::translate("UserTab", "User", nullptr));
        item->setText(QApplication::translate("UserTab", "Current order:", nullptr));
        name->setText(QApplication::translate("UserTab", "Name:", nullptr));
        id->setText(QApplication::translate("UserTab", "Chip no.", nullptr));
        edit->setText(QApplication::translate("UserTab", "Edit", nullptr));
        delete_2->setText(QApplication::translate("UserTab", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserTab: public Ui_UserTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERTAB_H
