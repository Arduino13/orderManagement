#include "search.h"
#include "ui_search.h"
#include <QCompleter>

search::search(QWidget *parent,QVector<User*> *users, QVector<Item*>* items) : QDialog(parent), ui(new Ui::search)
{
    ui->setupUi(this);

    buttonArray[NUMBER]=ui->number;
    buttonArray[BATCH]=ui->batch;
    buttonArray[STATE]=ui->state;
    buttonArray[USER]=ui->user;
    buttonArray[NUMBER_OF]=ui->number_of;
    buttonArray[DATE]=ui->date;

    map = new QSignalMapper(this);
    connect(map,SIGNAL(mapped(int)),this,SLOT(eventCatcher(int)));

    for(int i=0;i<BUTTON_NUM;i++){
        map->setMapping(buttonArray[i],i);
        connect(buttonArray[i],SIGNAL(toggled(bool)),map,SLOT(map()));
    }
    connect(ui->buttonBox,SIGNAL(clicked(QAbstractButton*)),this,SLOT(okButton(QAbstractButton*)));

    foreach(User *u, *users){
        ui->user_combo->addItem(u->getName());
    }
    for(int i=0;i<STATE_SIZES;i++){
        ui->state_combo->addItem(State::choises[i]);
    }
    ui->dateEdit->setDate(QDate::currentDate());

    QStringList completer_batch;
    QStringList completer_number;

    foreach(Item *i,*items){
        completer_batch<<i->getBatch();
        completer_number<<i->getNumber();
    }

    QCompleter *comp_batch = new QCompleter(completer_batch,this);
    QCompleter *comp_number = new QCompleter(completer_number,this);

    comp_batch->setCaseSensitivity(Qt::CaseInsensitive);
    comp_number->setCaseSensitivity(Qt::CaseInsensitive);

    ui->batch_edit->setCompleter(comp_batch);
    ui->number_edit->setCompleter(comp_number);
}

void search::eventCatcher(int i){
    switch(static_cast<int>(buttonArray_t[i])){
        case NUMBER:{
            if(buttonArray[i]->isChecked()) ui->number_edit->setEnabled(true);
            else ui->number_edit->setEnabled(false);
            break;
        }
        case BATCH:{
            if(buttonArray[i]->isChecked()) ui->batch_edit->setEnabled(true);
            else ui->batch_edit->setEnabled(false);
            break;
        }
        case NUMBER_OF:{
            if(buttonArray[i]->isChecked()) ui->number_of_edit->setEnabled(true);
            else ui->number_of_edit->setEnabled(false);
            break;
        }
        case USER:{
            if(buttonArray[i]->isChecked()) ui->user_combo->setEnabled(true);
            else ui->user_combo->setEnabled(false);
            break;
        }
        case STATE:{
            if(buttonArray[i]->isChecked()) ui->state_combo->setEnabled(true);
            else ui->state_combo->setEnabled(false);
            break;
        }
        case DATE:{
            if(buttonArray[i]->isChecked()) ui->dateEdit->setEnabled(true);
            else ui->dateEdit->setEnabled(false);
            break;
        }
    }
}

void search::okButton(QAbstractButton *){
    search_struct *structure = new search_struct;
    if(buttonArray[BATCH]->isChecked())structure->batch=ui->batch_edit->text();
    if(buttonArray[NUMBER]->isChecked())structure->number=ui->number_edit->text();
    if(buttonArray[NUMBER_OF]->isChecked())structure->number_of=ui->number_of_edit->text().toInt();
    if(buttonArray[STATE]->isChecked()) structure->state=State(State::str2state(ui->state_combo->currentText()));
    if(buttonArray[USER]->isChecked())structure->user_name=ui->user_combo->currentText();
    if(buttonArray[DATE]->isChecked()){
        structure->date=ui->dateEdit->date();
        if(ui->mothn_only->isChecked()) structure->month_only=true;
        else if(ui->year_only->isChecked()) structure->year_only=true;
    }
    result(structure);
}

search::~search(){
    for(int i=0;i<BUTTON_NUM;i++){
        disconnect(buttonArray[i],SIGNAL(clicked()));
    }
    disconnect(map,SIGNAL(mapped(int)));
    disconnect(ui->buttonBox,SIGNAL(clicked(QAbstractButton*)));

    delete ui->number_edit->completer();
    delete ui->batch_edit->completer();

    delete map;
    delete ui;
}
