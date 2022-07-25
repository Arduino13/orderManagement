/********************************************************************************
** Form generated from reading UI file 'password.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWORD_H
#define UI_PASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_password_d
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *lineEdit_2;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *checkBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *password_d)
    {
        if (password_d->objectName().isEmpty())
            password_d->setObjectName(QString::fromUtf8("password_d"));
        password_d->resize(400, 187);
        verticalLayout = new QVBoxLayout(password_d);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(password_d);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);

        gridLayout->addWidget(label, 1, 0, 1, 2);

        label_3 = new QLabel(password_d);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer_4, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 5, 0, 1, 1);

        lineEdit_2 = new QLineEdit(password_d);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_2, 3, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(30, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 0, 1, 1);

        checkBox = new QCheckBox(password_d);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 4, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        buttonBox = new QDialogButtonBox(password_d);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(password_d);
        QObject::connect(buttonBox, SIGNAL(accepted()), password_d, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), password_d, SLOT(reject()));

        QMetaObject::connectSlotsByName(password_d);
    } // setupUi

    void retranslateUi(QDialog *password_d)
    {
        password_d->setWindowTitle(QApplication::translate("password_d", "Dialog", nullptr));
        label->setText(QApplication::translate("password_d", "Login", nullptr));
        label_3->setText(QApplication::translate("password_d", "Password", nullptr));
        checkBox->setText(QApplication::translate("password_d", "Display password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class password_d: public Ui_password_d {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORD_H
