/********************************************************************************
** Form generated from reading UI file 'state_ch.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATE_CH_H
#define UI_STATE_CH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_state_ch
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGridLayout *gridLayout;
    QComboBox *state;
    QComboBox *type;
    QLabel *label_4;
    QDateTimeEdit *od;
    QLabel *label_3;
    QDateTimeEdit *do_2;
    QComboBox *type_c;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *user;
    QLabel *label_7;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *state_ch)
    {
        if (state_ch->objectName().isEmpty())
            state_ch->setObjectName(QString::fromUtf8("state_ch"));
        state_ch->resize(903, 156);
        verticalLayout = new QVBoxLayout(state_ch);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(state_ch);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        state = new QComboBox(state_ch);
        state->setObjectName(QString::fromUtf8("state"));

        gridLayout->addWidget(state, 1, 0, 1, 1);

        type = new QComboBox(state_ch);
        type->setObjectName(QString::fromUtf8("type"));

        gridLayout->addWidget(type, 1, 2, 1, 1);

        label_4 = new QLabel(state_ch);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 5, 1, 1);

        od = new QDateTimeEdit(state_ch);
        od->setObjectName(QString::fromUtf8("od"));
        od->setCalendarPopup(true);

        gridLayout->addWidget(od, 1, 4, 1, 1);

        label_3 = new QLabel(state_ch);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 4, 1, 1);

        do_2 = new QDateTimeEdit(state_ch);
        do_2->setObjectName(QString::fromUtf8("do_2"));
        do_2->setCalendarPopup(true);

        gridLayout->addWidget(do_2, 1, 5, 1, 1);

        type_c = new QComboBox(state_ch);
        type_c->setObjectName(QString::fromUtf8("type_c"));

        gridLayout->addWidget(type_c, 1, 3, 1, 1);

        label_2 = new QLabel(state_ch);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_5 = new QLabel(state_ch);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 2, 1, 1);

        label_6 = new QLabel(state_ch);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 3, 1, 1);

        user = new QComboBox(state_ch);
        user->setObjectName(QString::fromUtf8("user"));

        gridLayout->addWidget(user, 1, 1, 1, 1);

        label_7 = new QLabel(state_ch);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        buttonBox = new QDialogButtonBox(state_ch);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(state_ch);
        QObject::connect(buttonBox, SIGNAL(accepted()), state_ch, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), state_ch, SLOT(reject()));

        QMetaObject::connectSlotsByName(state_ch);
    } // setupUi

    void retranslateUi(QDialog *state_ch)
    {
        state_ch->setWindowTitle(QApplication::translate("state_ch", "Dialog", nullptr));
        label->setText(QApplication::translate("state_ch", "Edit", nullptr));
        label_4->setText(QApplication::translate("state_ch", "To:", nullptr));
        label_3->setText(QApplication::translate("state_ch", "From:", nullptr));
        label_2->setText(QApplication::translate("state_ch", "State:", nullptr));
        label_5->setText(QApplication::translate("state_ch", "Action:", nullptr));
        label_6->setText(QApplication::translate("state_ch", "Type:", nullptr));
        label_7->setText(QApplication::translate("state_ch", "User:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class state_ch: public Ui_state_ch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATE_CH_H
