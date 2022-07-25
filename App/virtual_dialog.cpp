#include "virtual_dialog.h"
#include "item_dialog.h"
#include "user_dialog.h"

template<class T>
virtual_dialog<T>::virtual_dialog(QWidget *parent, T ui, const QVector<User*>* users) : virtual_dialog_helper(parent)
{
    this->ui=ui;
    this->users=users;
    this->setWindowIcon(QIcon(":/new/prefix1/icon.png"));
}

template<class T>
T virtual_dialog<T>::getUi(){
    return ui;
}

template<class T>
void virtual_dialog<T>::setupTable(){
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setMouseTracking(true);
    ui->tableView->viewport()->installEventFilter(this);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableView->setStyleSheet("QTableView::item{border: 1px solid white; border-bottom: 1px solid rgb(51, 153, 255);}"
                                 "QTableView{gridline-color: white;} QHeaderView::section{ background-color: rgb(41, 143, 245); border-right: 2px solid white; border-bottom: 1px solid white; border-top: 0px solid white;"
                                 "border-left: 0px solid white; padding:4px;}"
                                 "alternate-background-color: rgb(255,255,255);background-color: gray;");
   this->setWindowState(Qt::WindowMaximized);
}

template<class T>
void virtual_dialog<T>::menuReq_wrapper(QPoint pos){
    menuReq(pos);
}

template<class T>
void virtual_dialog<T>::choose(const QItemSelection &, const QItemSelection &){
    if(!running){
        QMessageBox *box = DialogBoxes::InfoBox("Processing",true);
        box->show();
        QApplication::processEvents();

        running=true;
        QModelIndex index_m = ui->tableView->currentIndex();

        Item *item = db.loadItem(ui->tableView->model()->data(index_m,item_model_item::internal_id).toString());
        if(item->getID()!=""){

            QVector<Item*> temp({item});
            db.loadControlsTo(&temp);
            item_dialog *dialog = new item_dialog(NULL,item,users);//ne uplne spravne pouziti ale hodnoty

            windows.append(dialog);
            connect(dialog,SIGNAL(onClose(virtual_dialog_helper*)),this,SLOT(onClose_sub(virtual_dialog_helper*)));
            dialog->show();
        }
        delete item;
        ui->tableView->clearSelection();
        delete box;
        running=false;

        menuReq_wrapper(ui->tableView->viewport()->mapFromGlobal(QCursor::pos()));
    }
}

template<class T>
bool virtual_dialog<T>::eventFilter(QObject *watched, QEvent *event){
    if(event->type()==QEvent::MouseMove&&watched==ui->tableView->viewport()){
        QModelIndex index = ui->tableView->indexAt(dynamic_cast<QMouseEvent*>(event)->pos());
        for(int i=0;i<ui->tableView->model()->rowCount();i++){
            if(index.row()!=i) ui->tableView->setItemDelegateForRow(i,NULL);
            else ui->tableView->setItemDelegateForRow(i,&hover);
        }
    }
    return false;
}

template<class T>
void virtual_dialog<T>::onClose_sub(virtual_dialog_helper *dialog){
    windows.removeOne(dialog);
}

template<class T>
void virtual_dialog<T>::closeEvent(QCloseEvent *){
    this->deleteLater();
    foreach(virtual_dialog_helper *w,windows) delete w;
}

template<class T>
virtual_dialog<T>::~virtual_dialog(){
    onClose_support();
}

template class virtual_dialog<Ui::ItemTab*>;
template class virtual_dialog<Ui::UserTab*>;
