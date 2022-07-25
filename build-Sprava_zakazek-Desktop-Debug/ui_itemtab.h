/********************************************************************************
** Form generated from reading UI file 'itemtab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMTAB_H
#define UI_ITEMTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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

class Ui_ItemTab
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QPushButton *delete_2;
    QPushButton *edit;
    QLabel *label_6;
    QLineEdit *batch_edit;
    QLabel *label_7;
    QLineEdit *state_edit;
    QLineEdit *date_to_edit;
    QLineEdit *date_from_edit;
    QLabel *label_4;
    QLabel *item;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QLabel *id;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_4;
    QLabel *name;
    QLabel *label;
    QLineEdit *number_edit;
    QLabel *label_5;
    QSpacerItem *verticalSpacer_5;
    QLineEdit *user_edit;
    QLabel *label_8;
    QComboBox *thread_right_edit;
    QComboBox *thread_current_edit;
    QLabel *label_9;
    QLineEdit *numberof;
    QComboBox *thread_left_edit;
    QComboBox *first_control;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QComboBox *second_control;
    QLineEdit *reason_second;
    QLineEdit *reason_first;
    QSpacerItem *verticalSpacer_7;
    QTableView *tableView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ItemTab)
    {
        if (ItemTab->objectName().isEmpty())
            ItemTab->setObjectName(QString::fromUtf8("ItemTab"));
        ItemTab->resize(1366, 768);
        centralwidget = new QWidget(ItemTab);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        delete_2 = new QPushButton(centralwidget);
        delete_2->setObjectName(QString::fromUtf8("delete_2"));

        gridLayout->addWidget(delete_2, 25, 2, 1, 1);

        edit = new QPushButton(centralwidget);
        edit->setObjectName(QString::fromUtf8("edit"));

        gridLayout->addWidget(edit, 25, 0, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font;
        font.setPointSize(10);
        label_6->setFont(font);

        gridLayout->addWidget(label_6, 16, 0, 1, 1);

        batch_edit = new QLineEdit(centralwidget);
        batch_edit->setObjectName(QString::fromUtf8("batch_edit"));
        batch_edit->setEnabled(false);
        batch_edit->setReadOnly(false);

        gridLayout->addWidget(batch_edit, 7, 2, 1, 1);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        gridLayout->addWidget(label_7, 17, 0, 1, 1);

        state_edit = new QLineEdit(centralwidget);
        state_edit->setObjectName(QString::fromUtf8("state_edit"));
        state_edit->setEnabled(false);
        state_edit->setReadOnly(false);

        gridLayout->addWidget(state_edit, 8, 2, 1, 1);

        date_to_edit = new QLineEdit(centralwidget);
        date_to_edit->setObjectName(QString::fromUtf8("date_to_edit"));
        date_to_edit->setEnabled(false);
        date_to_edit->setReadOnly(false);

        gridLayout->addWidget(date_to_edit, 12, 2, 1, 1);

        date_from_edit = new QLineEdit(centralwidget);
        date_from_edit->setObjectName(QString::fromUtf8("date_from_edit"));
        date_from_edit->setEnabled(false);
        date_from_edit->setReadOnly(false);

        gridLayout->addWidget(date_from_edit, 11, 2, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font1;
        font1.setPointSize(20);
        label_4->setFont(font1);

        gridLayout->addWidget(label_4, 3, 0, 1, 4);

        item = new QLabel(centralwidget);
        item->setObjectName(QString::fromUtf8("item"));
        item->setFont(font);

        gridLayout->addWidget(item, 8, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 5, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 19, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 5, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 12, 0, 1, 1);

        id = new QLabel(centralwidget);
        id->setObjectName(QString::fromUtf8("id"));
        id->setFont(font);

        gridLayout->addWidget(id, 7, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer_3, 4, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 11, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer_4, 13, 0, 1, 1);

        name = new QLabel(centralwidget);
        name->setObjectName(QString::fromUtf8("name"));
        name->setFont(font);

        gridLayout->addWidget(name, 5, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 9, 0, 1, 1);

        number_edit = new QLineEdit(centralwidget);
        number_edit->setObjectName(QString::fromUtf8("number_edit"));
        number_edit->setEnabled(false);
        number_edit->setReadOnly(false);

        gridLayout->addWidget(number_edit, 5, 2, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);

        gridLayout->addWidget(label_5, 14, 0, 1, 4);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer_5, 15, 0, 1, 1);

        user_edit = new QLineEdit(centralwidget);
        user_edit->setObjectName(QString::fromUtf8("user_edit"));
        user_edit->setEnabled(false);
        user_edit->setReadOnly(false);

        gridLayout->addWidget(user_edit, 9, 2, 1, 1);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);

        gridLayout->addWidget(label_8, 18, 0, 1, 1);

        thread_right_edit = new QComboBox(centralwidget);
        thread_right_edit->setObjectName(QString::fromUtf8("thread_right_edit"));
        thread_right_edit->setEnabled(false);
        thread_right_edit->setEditable(false);

        gridLayout->addWidget(thread_right_edit, 17, 2, 1, 1);

        thread_current_edit = new QComboBox(centralwidget);
        thread_current_edit->setObjectName(QString::fromUtf8("thread_current_edit"));
        thread_current_edit->setEnabled(false);
        thread_current_edit->setEditable(false);

        gridLayout->addWidget(thread_current_edit, 18, 2, 1, 1);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);

        gridLayout->addWidget(label_9, 10, 0, 1, 1);

        numberof = new QLineEdit(centralwidget);
        numberof->setObjectName(QString::fromUtf8("numberof"));
        numberof->setEnabled(false);
        numberof->setReadOnly(false);

        gridLayout->addWidget(numberof, 10, 2, 1, 1);

        thread_left_edit = new QComboBox(centralwidget);
        thread_left_edit->setObjectName(QString::fromUtf8("thread_left_edit"));
        thread_left_edit->setEnabled(false);
        thread_left_edit->setEditable(false);

        gridLayout->addWidget(thread_left_edit, 16, 2, 1, 1);

        first_control = new QComboBox(centralwidget);
        first_control->setObjectName(QString::fromUtf8("first_control"));
        first_control->setEnabled(false);
        first_control->setEditable(false);

        gridLayout->addWidget(first_control, 22, 2, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_6, 24, 0, 1, 1);

        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font1);

        gridLayout->addWidget(label_10, 20, 0, 1, 1);

        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font);

        gridLayout->addWidget(label_11, 22, 0, 1, 1);

        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font);

        gridLayout->addWidget(label_12, 23, 0, 1, 1);

        second_control = new QComboBox(centralwidget);
        second_control->setObjectName(QString::fromUtf8("second_control"));
        second_control->setEnabled(false);
        second_control->setEditable(false);

        gridLayout->addWidget(second_control, 23, 2, 1, 1);

        reason_second = new QLineEdit(centralwidget);
        reason_second->setObjectName(QString::fromUtf8("reason_second"));
        reason_second->setEnabled(false);
        reason_second->setReadOnly(false);

        gridLayout->addWidget(reason_second, 23, 3, 1, 1);

        reason_first = new QLineEdit(centralwidget);
        reason_first->setObjectName(QString::fromUtf8("reason_first"));
        reason_first->setEnabled(false);
        reason_first->setReadOnly(false);

        gridLayout->addWidget(reason_first, 22, 3, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer_7, 21, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(tableView);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);
        ItemTab->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ItemTab);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1366, 22));
        ItemTab->setMenuBar(menubar);
        statusbar = new QStatusBar(ItemTab);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ItemTab->setStatusBar(statusbar);

        retranslateUi(ItemTab);

        QMetaObject::connectSlotsByName(ItemTab);
    } // setupUi

    void retranslateUi(QMainWindow *ItemTab)
    {
        ItemTab->setWindowTitle(QApplication::translate("ItemTab", "Order card", nullptr));
        delete_2->setText(QApplication::translate("ItemTab", "Delete", nullptr));
        edit->setText(QApplication::translate("ItemTab", "Edit", nullptr));
        label_6->setText(QApplication::translate("ItemTab", "First side:", nullptr));
        label_7->setText(QApplication::translate("ItemTab", "Second side:", nullptr));
        label_4->setText(QApplication::translate("ItemTab", "Order", nullptr));
        item->setText(QApplication::translate("ItemTab", "State:", nullptr));
        label_3->setText(QApplication::translate("ItemTab", "End date:", nullptr));
        id->setText(QApplication::translate("ItemTab", "Batch no. :", nullptr));
        label_2->setText(QApplication::translate("ItemTab", "Start date:", nullptr));
        name->setText(QApplication::translate("ItemTab", "Drawing no. :", nullptr));
        label->setText(QApplication::translate("ItemTab", "User:", nullptr));
        label_5->setText(QApplication::translate("ItemTab", "Thread", nullptr));
        label_8->setText(QApplication::translate("ItemTab", "Rolled:", nullptr));
        label_9->setText(QApplication::translate("ItemTab", "Pieces: ", nullptr));
        label_10->setText(QApplication::translate("ItemTab", "Controls:", nullptr));
        label_11->setText(QApplication::translate("ItemTab", "First:", nullptr));
        label_12->setText(QApplication::translate("ItemTab", "Second:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ItemTab: public Ui_ItemTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMTAB_H
