#include "password_dialog.h"
#include "ui_password.h"

password_dialog::password_dialog(QWidget *parent,bool add) : QDialog(parent), ui(new Ui::password_d)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(clicked(QAbstractButton*)),this,SLOT(buttonClick(QAbstractButton*)));
    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(passHide(bool)));
    this->add=add;
    this->setWindowTitle(add ? "Type new password" : "Login");
    this->setWindowIcon(QIcon(":/new/prefix1/icon.png"));
}

void password_dialog::buttonClick(QAbstractButton *b){
    if(b->text()=="&OK" || b->text() == "OK"){
        if(!add){
            QString pas;
            try{
                pas = db.confLoad("password");
            }catch(exception *e){
                error(e);
                qDebug() << e->reason();
                return;
            }

            QByteArray encrypt(ui->lineEdit_2->text().toStdString().c_str());
            encrypt = QCryptographicHash::hash(encrypt,QCryptographicHash::Sha512).toHex();

            if(pas==QString::fromStdString(encrypt.toStdString())){
                result(true);
            }
            else{
                result(false);
            }
        }
        else{
            QByteArray encrypt(ui->lineEdit_2->text().toStdString().c_str());
            encrypt = QCryptographicHash::hash(encrypt,QCryptographicHash::Sha512).toHex();
            result(QString::fromStdString(encrypt.toStdString()));
        }
    }
    else{
        if(add) result("");
        else result(false);
    }
}

void password_dialog::passHide(bool){
    if(ui->checkBox->isChecked()){
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    }
    else{
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }
}

password_dialog::~password_dialog(){
    disconnect(ui->buttonBox,SIGNAL(clicked(QAbstractButton*)));
    disconnect(ui->checkBox,SIGNAL(clicked(bool)));
    delete ui;
}
