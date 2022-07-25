#include "setting.h"
#include "ui_setting.h"
#include "dialogboxes.h"
Setting::Setting(QWidget *parent) : QDialog(parent), ui(new Ui::setting)
{
    type2str[THREADS]="conf_threads_list";

    QVector<QString> list = loadThread_list();

    ui->setupUi(this);

    ui->tableWidget->setColumnCount(COLUM_NUM_SET);
    ui->tableWidget->setRowCount(list.size());
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->setStyleSheet("");
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i=0;i < ui->tableWidget->horizontalHeader()->count();i++){
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }

    map = new QSignalMapper(this);
    connect(map,SIGNAL(mapped(int)),this,SLOT(removeEvent(int)));

    for(int i=0;i<ui->tableWidget->rowCount();i++){
        QLabel *label = new QLabel(list.at(i));
        QPushButton *button = new QPushButton("Remove");

        map->setMapping(button,i);
        connect(button,SIGNAL(clicked()),map,SLOT(map()));

        ui->tableWidget->setCellWidget(i,TEXT,label);
        ui->tableWidget->setCellWidget(i,BUTTON,button);
    }
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(addEvent(bool)));
}

void Setting::addEvent(bool){
    if(ui->lineEdit->text()!=""){
        QVector<QString> temp = loadThread_list();
        temp.append(ui->lineEdit->text());

        if(!saveThread_list(temp)){
            DialogBoxes::ErrorBox("Error occured, while saving");
        }
        addToTable(ui->lineEdit->text());
        ui->lineEdit->clear();
    }
}

void Setting::removeEvent(int row){
    QString text = dynamic_cast<QLabel*>(ui->tableWidget->cellWidget(row,TEXT))->text();
    QVector<QString> temp = loadThread_list();
    temp.removeOne(text);
    if(!saveThread_list(temp)) DialogBoxes::ErrorBox("Error occured, while saving");

    ui->tableWidget->removeRow(row);
}

void Setting::addToTable(QString str){
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

    int i=ui->tableWidget->rowCount()-1;

    QLabel *label = new QLabel(str);
    QPushButton *button = new QPushButton("Remove");

    ui->tableWidget->setCellWidget(i,TEXT,label);
    ui->tableWidget->setCellWidget(i,BUTTON,button);
}

QVector<QString> Setting::loadThread_list(){
    QString result = db.confLoad(type2str[THREADS]);
    if(result!=""){
        result.remove(result.lastIndexOf(';'),1);

        return result.split(";").toVector();
    }
    return QVector<QString>();
}

bool Setting::saveThread_list(QVector<QString> save){
    QString to_save;
    foreach(QString s, save){
        to_save+=(s+";");
    }

    return db.confSave(type2str[THREADS],to_save);
}

Setting::~Setting(){
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        disconnect(dynamic_cast<QPushButton*>(ui->tableWidget->cellWidget(i,BUTTON)),SIGNAL(clicked()));
        delete ui->tableWidget->cellWidget(i,TEXT);
        delete ui->tableWidget->cellWidget(i,BUTTON);
    }
    disconnect(map,SIGNAL(mapped(int)));
    disconnect(ui->pushButton,SIGNAL(clicked(bool)));

    delete map;
    delete ui;
}
