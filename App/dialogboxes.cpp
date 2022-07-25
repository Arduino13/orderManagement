#include "dialogboxes.h"
#include <QAbstractButton>

DialogBoxes::DialogBoxes()
{

}

void DialogBoxes::ErrorBox(const QString msg){
    QMessageBox boxEthernet;
    boxEthernet.setIcon(QMessageBox::Critical);
    boxEthernet.setText(msg);

    Log::ErrorLog(msg);

    boxEthernet.setWindowIcon(QIcon(":/new/prefix1/icon.png"));
    boxEthernet.exec();
}

void DialogBoxes::InfoBox(const QString msg){
    QMessageBox boxEthernet;
    boxEthernet.setIcon(QMessageBox::Information);
    boxEthernet.setText(msg);

    Log::InfoLog(msg);

    boxEthernet.setWindowIcon(QIcon(":/new/prefix1/icon.png"));
    boxEthernet.exec();
}

QMessageBox* DialogBoxes::InfoBox(const QString msg, bool){
    QMessageBox* boxEthernet = new QMessageBox();
    boxEthernet->setIcon(QMessageBox::Information);
    boxEthernet->setText(msg);

    Log::InfoLog(msg);

    boxEthernet->setWindowIcon(QIcon(":/new/prefix1/icon.png"));
    return boxEthernet;
}
void DialogBoxes::WarningBox(const QString msg){
    QMessageBox boxEthernet;
    boxEthernet.setIcon(QMessageBox::Warning);
    boxEthernet.setText(msg);

    Log::WarningLog(msg);

    boxEthernet.setWindowIcon(QIcon(":/new/prefix1/icon.png"));
    boxEthernet.exec();
}

bool DialogBoxes::ConfBox(const QString msg){
    QMessageBox box;
    box.setIcon(QMessageBox::Warning);
    box.setText(msg);
    box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    box.setDefaultButton(QMessageBox::No);
    box.setWindowIcon(QIcon(":/new/prefix1/icon.png"));
    box.exec();

    return box.clickedButton()->text()=="&Yes";
}
