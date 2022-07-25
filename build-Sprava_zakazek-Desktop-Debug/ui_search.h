/********************************************************************************
** Form generated from reading UI file 'search.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCH_H
#define UI_SEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_search
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QRadioButton *number;
    QRadioButton *batch;
    QRadioButton *state;
    QRadioButton *user;
    QRadioButton *number_of;
    QRadioButton *date;
    QGridLayout *gridLayout;
    QLineEdit *batch_edit;
    QLineEdit *number_of_edit;
    QComboBox *state_combo;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *number_edit;
    QLabel *label_2;
    QLabel *label_6;
    QComboBox *user_combo;
    QLabel *label_7;
    QLabel *label_5;
    QDateEdit *dateEdit;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *mothn_only;
    QCheckBox *year_only;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *search)
    {
        if (search->objectName().isEmpty())
            search->setObjectName(QString::fromUtf8("search"));
        search->resize(552, 293);
        verticalLayout = new QVBoxLayout(search);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(search);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        number = new QRadioButton(search);
        number->setObjectName(QString::fromUtf8("number"));
        number->setAutoExclusive(false);

        horizontalLayout->addWidget(number);

        batch = new QRadioButton(search);
        batch->setObjectName(QString::fromUtf8("batch"));
        batch->setAutoExclusive(false);

        horizontalLayout->addWidget(batch);

        state = new QRadioButton(search);
        state->setObjectName(QString::fromUtf8("state"));
        state->setAutoExclusive(false);

        horizontalLayout->addWidget(state);

        user = new QRadioButton(search);
        user->setObjectName(QString::fromUtf8("user"));
        user->setAutoExclusive(false);

        horizontalLayout->addWidget(user);

        number_of = new QRadioButton(search);
        number_of->setObjectName(QString::fromUtf8("number_of"));
        number_of->setAutoExclusive(false);

        horizontalLayout->addWidget(number_of);

        date = new QRadioButton(search);
        date->setObjectName(QString::fromUtf8("date"));

        horizontalLayout->addWidget(date);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        batch_edit = new QLineEdit(search);
        batch_edit->setObjectName(QString::fromUtf8("batch_edit"));
        batch_edit->setEnabled(false);

        gridLayout->addWidget(batch_edit, 5, 0, 1, 1);

        number_of_edit = new QLineEdit(search);
        number_of_edit->setObjectName(QString::fromUtf8("number_of_edit"));
        number_of_edit->setEnabled(false);

        gridLayout->addWidget(number_of_edit, 7, 0, 1, 1);

        state_combo = new QComboBox(search);
        state_combo->setObjectName(QString::fromUtf8("state_combo"));
        state_combo->setEnabled(false);

        gridLayout->addWidget(state_combo, 7, 2, 1, 1);

        label_4 = new QLabel(search);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 6, 0, 1, 1);

        label_3 = new QLabel(search);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        number_edit = new QLineEdit(search);
        number_edit->setObjectName(QString::fromUtf8("number_edit"));
        number_edit->setEnabled(false);

        gridLayout->addWidget(number_edit, 1, 0, 1, 1);

        label_2 = new QLabel(search);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_6 = new QLabel(search);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 4, 2, 1, 1);

        user_combo = new QComboBox(search);
        user_combo->setObjectName(QString::fromUtf8("user_combo"));
        user_combo->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(user_combo->sizePolicy().hasHeightForWidth());
        user_combo->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(user_combo, 5, 2, 1, 1);

        label_7 = new QLabel(search);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 6, 2, 1, 1);

        label_5 = new QLabel(search);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 2, 1, 1);

        dateEdit = new QDateEdit(search);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setEnabled(false);
        dateEdit->setWrapping(false);
        dateEdit->setCalendarPopup(true);

        gridLayout->addWidget(dateEdit, 1, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        mothn_only = new QCheckBox(search);
        mothn_only->setObjectName(QString::fromUtf8("mothn_only"));
        mothn_only->setAutoExclusive(false);

        horizontalLayout_2->addWidget(mothn_only);

        year_only = new QCheckBox(search);
        year_only->setObjectName(QString::fromUtf8("year_only"));
        year_only->setAutoExclusive(false);

        horizontalLayout_2->addWidget(year_only);


        gridLayout->addLayout(horizontalLayout_2, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        buttonBox = new QDialogButtonBox(search);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 5);
        verticalLayout->setStretch(3, 1);

        retranslateUi(search);
        QObject::connect(buttonBox, SIGNAL(accepted()), search, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), search, SLOT(reject()));

        QMetaObject::connectSlotsByName(search);
    } // setupUi

    void retranslateUi(QDialog *search)
    {
        search->setWindowTitle(QApplication::translate("search", "Dialog", nullptr));
        label->setText(QApplication::translate("search", "Search", nullptr));
        number->setText(QApplication::translate("search", "Drawing no.", nullptr));
        batch->setText(QApplication::translate("search", "Batch no.", nullptr));
        state->setText(QApplication::translate("search", "State", nullptr));
        user->setText(QApplication::translate("search", "User", nullptr));
        number_of->setText(QApplication::translate("search", "Pieces", nullptr));
        date->setText(QApplication::translate("search", "Date", nullptr));
        label_4->setText(QApplication::translate("search", "Pieces", nullptr));
        label_3->setText(QApplication::translate("search", "Batch no.", nullptr));
        label_2->setText(QApplication::translate("search", "Drawing no.", nullptr));
        label_6->setText(QApplication::translate("search", "User", nullptr));
        label_7->setText(QApplication::translate("search", "State", nullptr));
        label_5->setText(QApplication::translate("search", "Date", nullptr));
        mothn_only->setText(QApplication::translate("search", "Only month", nullptr));
        year_only->setText(QApplication::translate("search", "Only year", nullptr));
    } // retranslateUi

};

namespace Ui {
    class search: public Ui_search {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCH_H
