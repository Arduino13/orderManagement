#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    password_dialog dialog;
    bool correct=false;
    connect(&dialog,static_cast<int (password_dialog::*)(bool)>(&password_dialog::result),this,[&correct](bool corr){correct=corr;});
    connect(&dialog,SIGNAL(error(exception*)),this,SLOT(error(exception*)));
	//displays password prompt
    dialog.exec();

    if(error_c) throw new exception("connection error");
    if(!correct) throw new exception("auth error");
    disconnect(&dialog,SIGNAL(result(bool)));
    disconnect(&dialog,SIGNAL(error(exception*)));

    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/new/prefix1/icon.png"));
    this->setWindowTitle("Orders manager 1.0 pre-alpha");

    users=db.loadListUser();
    items=new QVector<Item*>();
    items_search= new QVector<Item*>();
    if(!reloadTable(false)) throw new exception("fatal error");

    ui->tableView->verticalHeader()->hide();
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setMouseTracking(true);
    ui->tableView->viewport()->installEventFilter(this);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setStyleSheet("QTableView::item{border: 1px solid white; border-bottom: 1px solid rgb(51, 153, 255);}"
                                 "QTableView{gridline-color: white;} QHeaderView::section{ background-color: rgb(41, 143, 245); border-right: 2px solid white; border-bottom: 1px solid white; border-top: 0px solid white;"
                                 "border-left: 0px solid white; padding:4px;}"
                                 "alternate-background-color: rgb(255,255,255);background-color: gray;");

    hover=new hover_delegate();

    connect(ui->actionU_ivatel,SIGNAL(triggered(bool)),this,SLOT(reloadTable(bool)));
    connect(ui->actionZak_zky,SIGNAL(triggered(bool)),this,SLOT(reloadTable(bool)));
    connect(ui->menuObnovit,SIGNAL(aboutToShow()),this,SLOT(reloadTable()));
    connect(ui->actionPodle_id,SIGNAL(triggered(bool)),this,SLOT(items_sort(bool)));
    connect(ui->actionPodle_sla_v_kresu,SIGNAL(triggered(bool)),this,SLOT(items_sort(bool)));
    connect(ui->actionSeznam_z_vit,SIGNAL(triggered(bool)),this,SLOT(run_setting(bool)));
    connect(ui->menuHledat,SIGNAL(aboutToShow()),this,SLOT(run_search()));
    connect(ui->actionSmazat_historii,SIGNAL(triggered(bool)),this,SLOT(Delete_all(bool)));
    connect(ui->actionZm_nit_heslo,SIGNAL(triggered(bool)),this,SLOT(change_password(bool)));
}

void MainWindow::error(exception *e){
    delete e;
    error_c=true;
}

void MainWindow::run_setting(bool){
    Setting setting(this);
    setting.exec();
}

void MainWindow::run_search(){
    search s(this,users,items);
    connect(&s,SIGNAL(result(search::search_struct*)),this,SLOT(reloadTable(search::search_struct*)));
    s.exec();
    disconnect(&s,SIGNAL(result(search::search_struct*)));
}

void MainWindow::Delete_all(bool){
    if(DialogBoxes::ConfBox("Do you really want to delete history records of all orders ?")){
        db.deleteHistory();
    }
}

void MainWindow::change_password(bool){
    password_dialog dialog(this,true);
    QString value="";
    connect(&dialog,static_cast<int (password_dialog::*)(QString)>(&password_dialog::result),this,[&value](QString s){value=s;});
    dialog.exec();
    if(value!="") db.confSave("password",value);
    disconnect(&dialog,SIGNAL(result(QString)));
}

void MainWindow::choose(const QItemSelection &, const QItemSelection &){
   if(!running){
       QMessageBox *box = DialogBoxes::InfoBox("Processing",true);
       box->show();
       QApplication::processEvents();

        running=true;
        QModelIndex index_m = ui->tableView->currentIndex();

        if(prev_ch==ITEMS){
            Item *item = NULL;
            foreach(Item* temp,*items){
                if(ui->tableView->model()->data(index_m,main_model_item::internal_id)==temp->getID()) item=temp;
            }

           if(prev_ch_items==BY_ID){
             item_dialog *dialog = new item_dialog(NULL,item,users);
             windows.append(dialog);
             connect(dialog,SIGNAL(onClose(virtual_dialog_helper*)),this,SLOT(dialog_on_close(virtual_dialog_helper*)));
             connect(dialog,SIGNAL(reloadMain(bool)),this,SLOT(reloadTable(bool)));
             dialog->show();
            }
           else if(prev_ch_items==BY_NUMBER){
             item_dialog *dialog = new item_dialog(NULL,item,users,items);
             windows.append(dialog);
             connect(dialog,SIGNAL(onClose(virtual_dialog_helper*)),this,SLOT(dialog_on_close(virtual_dialog_helper*)));
             connect(dialog,SIGNAL(reloadMain(bool)),this,SLOT(reloadTable(bool)));
             dialog->show();
           }
        }

        else{
            User *user=db.loadUser(ui->tableView->model()->data(index_m,main_model_user::internal_id).toString());
            user_dialog *dialog = new user_dialog(NULL,user,items,users);
            windows.append(dialog);
            connect(dialog,SIGNAL(onClose(virtual_dialog_helper*)),this,SLOT(dialog_on_close(virtual_dialog_helper*)));
            connect(this,SIGNAL(dataChanged(QVector<Item*>*)),dialog,SLOT(reloadData(QVector<Item*>*)));
            connect(dialog,SIGNAL(reloadMain(bool)),this,SLOT(reloadTable(bool)));
            dialog->show();

            delete user;
        }

        ui->tableView->clearSelection();
        delete box;
        running=false;
   }
}

void MainWindow::dialog_on_close(virtual_dialog_helper *dialog){
    disconnect(dialog,SIGNAL(onClose(virtual_dialog_helper*)));
    disconnect(dialog,SIGNAL(reloadMain(bool)));
    windows.removeOne(dialog);
}

//TODO create interface for search to replace search_struct 
void MainWindow::reloadData(search::search_struct *item){ 
    QVector<Item*>* temp = db.loadListItem();

    if(item==NULL){
        foreach(Item *i, *items) delete i;

        items->clear();
    }
    else{
        foreach(Item *i, *items_search) delete i;

        items_search->clear();
    }
    foreach(Item *i, *temp){
        if(item==NULL){
            items->append(i);
        }
        else{
            bool append=false; //TODO: fix append

            if(item->batch!=""){
                append=i->getBatch()==item->batch;
            }
            if(item->number!=""){
                append=i->getNumber()==item->number;
            }
            if(item->number_of!=0){
                append=i->getNumberOf()==item->number_of;
            }
            if(item->state.isValid()){
                append=*i->getState()==item->state;
            }
            if(item->user_name!=""){
                append=i->getUser()->getName()==item->user_name;
            }
            if(item->date.isValid()){
                if(!item->month_only&&!item->year_only) append=i->getDateFrom().date()==item->date;
                else if(item->month_only) append=(i->getDateFrom().date().month()==item->date.month()&&i->getDateFrom().date().year()==item->date.year());
                else if(item->year_only) append=i->getDateFrom().date().year()==item->date.year();
            }

            if(append) items_search->append(i);
        }
    }

    db.loadControlsTo(items);

    if(item==NULL) dataChanged(items);
    else delete item;

    delete temp;

    QThread::msleep(1000);
}

bool MainWindow::reloadTable(search::search_struct *item){
    return reloadTable(false,item);
}

bool MainWindow::reloadTable(bool not_first, search::search_struct *item){ 
    QMessageBox *box = DialogBoxes::InfoBox("Processing",true);
    box->show();
    QApplication::processEvents(); //to draw message box

    disconnect(ui->tableView->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)));

    if(ui->actionU_ivatel->isChecked()&&(prev_ch!=USERS||!not_first)){
        try{
            reloadData(item);
            QVector<Item*>* selected = (item==NULL ? items : items_search);
            main_model_user *user = new main_model_user(this,users,selected);
            QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
            proxyModel->setSourceModel(user);

            if(will_remove){
                delete (dynamic_cast<QSortFilterProxyModel*>(ui->tableView->model()))->sourceModel();
                delete ui->tableView->model();
            }

            ui->tableView->setModel(proxyModel);
            ui->tableView->setSortingEnabled(true);
            ui->actionZak_zky->setChecked(false);
            prev_ch=USERS;
        }catch(exception *e){
            ui->actionU_ivatel->setChecked(false);
            DialogBoxes::ErrorBox("Connection to database is currently not available");
            delete e;
            delete box;
            return false;
        }
    }
    else if(ui->actionZak_zky->isChecked()&&(prev_ch!=ITEMS||!not_first)){
        try{
            reloadData(item);
            QVector<Item*>* selected = (item==NULL ? items : items_search);
            main_model_item *item = new main_model_item(this,selected);
            QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
            proxyModel->setSourceModel(item);

            if(will_remove){
                delete (dynamic_cast<QSortFilterProxyModel*>(ui->tableView->model()))->sourceModel();
                delete ui->tableView->model();
            }

            ui->tableView->setModel(proxyModel);
            ui->tableView->setSortingEnabled(true);
            ui->actionU_ivatel->setChecked(false);
            prev_ch=ITEMS;
        }catch(exception *e){
            ui->actionZak_zky->setChecked(false);
            DialogBoxes::ErrorBox("Connection to database is currently not available");
            delete e;
            delete box;
            return false;
        }
    }

    delete box;
    this->resizeEvent(NULL);
    will_remove=true;

    connect(ui->tableView->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(choose(QItemSelection,QItemSelection)));

    return true;
}

void MainWindow::items_sort(bool){
    if(ui->actionPodle_id->isChecked()&&(prev_ch_items!=BY_ID)){
        ui->actionPodle_sla_v_kresu->setChecked(false);
        prev_ch_items=BY_ID;
    }
    else if(ui->actionPodle_sla_v_kresu->isChecked()){
        ui->actionPodle_id->setChecked(false);
        prev_ch_items=BY_NUMBER;
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event){
    if(event->type()==QEvent::MouseMove&&watched==ui->tableView->viewport()){
        QModelIndex index = ui->tableView->indexAt(dynamic_cast<QMouseEvent*>(event)->pos());
        for(int i=0;i<ui->tableView->model()->rowCount();i++){
            if(index.row()!=i) ui->tableView->setItemDelegateForRow(i,NULL);
            else ui->tableView->setItemDelegateForRow(i,hover);
        }
    }
    return false;
}

void MainWindow::resizeEvent(QResizeEvent *){
    int colum_num = ui->actionU_ivatel->isChecked() ? COLUM_NUM_U : COLUM_NUM;

    for(int i=0;i<colum_num;i++){
        ui->tableView->setColumnWidth(i,this->width()/colum_num);
    }
}

void MainWindow::closeEvent(QCloseEvent *){
    foreach(virtual_dialog_helper *w, windows){
        disconnect(w,SIGNAL(onClose(virtual_dialog_helper*)));
        w->close();
    }
}

MainWindow::~MainWindow()
{
    delete hover;
    delete (dynamic_cast<QSortFilterProxyModel*>(ui->tableView->model()))->sourceModel();
    delete ui->tableView->model();
    delete ui;
}
