#include "user_dialog.h"
#include "item_dialog.h"
#include "dialogboxes.h"
#include <QMessageBox>

user_dialog::user_dialog(QWidget *parent, const User *user_temp, const QVector<Item*>* list, const QVector<User *> *users) : virtual_dialog(parent,new Ui::UserTab,users)
{
    ui=getUi();

    ui->setupUi(this);
    ui->id_edit->setText(user_temp->getCardNumber());
    ui->name_edit->setText(user_temp->getName());

    user=*user_temp;

    ui->item_edit->setText("None");
    foreach(Item *i,*list){
        if(*i->getUser()==*user_temp&&i->getState()->getState()!=State::completed){
            ui->item_edit->setText(i->getNumber());
            break;
        }
    }

    setupTable();

    user_model_user *userM = new user_model_user(this,&user,list);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(userM);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    for(int i = 0; i< ui->tableView->horizontalHeader()->count();i++){
        ui->tableView->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }

    connect(ui->tableView->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(choose(QItemSelection,QItemSelection)));
    connect(ui->edit,SIGNAL(clicked(bool)),this,SLOT(editMode(bool)));
    connect(ui->delete_2,SIGNAL(clicked(bool)),this,SLOT(remove(bool)));
}

void user_dialog::editMode(bool){
    ui->name_edit->setEnabled(true);
    edit_mode=true;
}

void user_dialog::remove(bool){
    if(DialogBoxes::ConfBox("Do you reall want to delete this user ?")){
        if(!db.deleteUser(&user)) DialogBoxes::ErrorBox("Error occured, while saving");
        reloadMain(false);
        this->deleteLater();
    }
}

void user_dialog::closeEvent(QCloseEvent *e){
    if(edit_mode){
        if(ui->name_edit->text()!=""){
            User user_2(user.getId(),ui->name_edit->text(),user.getCardNumber());
            if(!db.saveUser(&user_2)) DialogBoxes::ErrorBox("Error occured, while saving");
            reloadMain(false);
        }
        else DialogBoxes::ErrorBox("Incorrect format of input data, changes were not saved");
    }

    virtual_dialog::closeEvent(e);
}

void user_dialog::reloadData(QVector<Item *> *data){
    delete (dynamic_cast<QSortFilterProxyModel*>(ui->tableView->model()))->sourceModel();
    delete ui->tableView->model();

    user_model_user *userM = new user_model_user(this,&user,data);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(userM);
    ui->tableView->setModel(proxyModel);
}


user_dialog::~user_dialog(){
    disconnect(ui->tableView->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)));
    disconnect(ui->delete_2,SIGNAL(clicked(bool)));
    disconnect(ui->edit,SIGNAL(clicked(bool)));

    delete (dynamic_cast<QSortFilterProxyModel*>(ui->tableView->model()))->sourceModel();
    delete ui->tableView->model();
    delete ui;
}
