#include "item_dialog.h"
#include <QMessageBox>
#include "dialogboxes.h"
#include "setting.h"

item_dialog::item_dialog(QWidget *parent, const Item *item, const QVector<User *> *users, QVector<Item*>* items) : virtual_dialog(parent,new Ui::ItemTab,users)
{
    ui=virtual_dialog::getUi();

    validScrew = item->getScrew()==NULL ? false : true;
    controls_valid[0] = item->getControl(Item::FIRST_c)->empty() ? false : true;
    controls_valid[1] = item->getControl(Item::SECOND_c)->empty() ? false : true;

    listID.item_s=*item;
    if(validScrew) listID.screw_id=item->getScrew()->getId();
    listID.user=listID.item_s.getUser();
    listID.users=users;

    ui->setupUi(this);
    this->by_number= items==NULL ? false : true;
    this->items=items;

    ui->batch_edit->setText(item->getBatch());
    ui->number_edit->setText(item->getNumber());

    if(!by_number){
        ui->date_from_edit->setText(item->getDateFrom().toString("dd.MM.yyyy HH:mm"));
        ui->date_to_edit->setText(item->getDateTo().toString("dd.MM.yyyy HH:mm"));
        ui->numberof->setText(QString::number(item->getNumberOf()));
        ui->user_edit->setText(item->getUser()->getName());
        ui->state_edit->setText(item->getState()->toString());

        if(validScrew){
            Setting set;
            foreach(QString s,set.loadThread_list()){
                ui->thread_left_edit->addItem(s);
                ui->thread_right_edit->addItem(s);
            }
            ui->thread_current_edit->addItem(FIRST);
            ui->thread_current_edit->addItem(SECOND);
            ui->thread_current_edit->addItem(UNKNOWN);
			
            ui->thread_left_edit->addItem(item->getScrew()->getT(Item::Screw::LEFT));
            ui->thread_right_edit->addItem(item->getScrew()->getT(Item::Screw::RIGHT));

            ui->thread_left_edit->setCurrentText(item->getScrew()->getT(Item::Screw::LEFT));
            ui->thread_right_edit->setCurrentText(item->getScrew()->getT(Item::Screw::RIGHT));
            switch(static_cast<int>(item->getScrew()->getC())){
                case Item::Screw::LEFT:
                    ui->thread_current_edit->setCurrentText(FIRST);
                    break;
                case Item::Screw::RIGHT:
                    ui->thread_current_edit->setCurrentText(SECOND);
                    break;
                case Item::Screw::UNKNOW:
                    ui->thread_current_edit->setCurrentText(UNKNOWN);
            }
        }
    }
    else{
        QDateTime latest=item->getDateFrom();
        QDateTime first=item->getDateFrom();
        bool was_latest=false;
        int count=0;
        foreach(Item *i,*items){
            if(i->getBatch()==item->getBatch()&&i->getNumber()==item->getNumber()){ //TODO: fix, control is with this setting not unique
                if(i->getDateFrom()<first) first=i->getDateFrom();
                if(i->getDateTo()>latest) {latest=i->getDateTo(); was_latest=true;}
                count += i->getNumberOf();
            }
        }
        ui->date_from_edit->setText(first.toString("dd.MM.yyyy HH:mm"));
        if(was_latest) ui->date_to_edit->setText(latest.toString("dd.MM.yyyy HH:mm"));
        ui->numberof->setText(QString::number(count));
        ui->thread_left_edit->addItem(item->getScrew()->getT(Item::Screw::LEFT));
        ui->thread_right_edit->addItem(item->getScrew()->getT(Item::Screw::RIGHT));
    }

    //displays controls
    if(controls_valid[static_cast<int>(Item::FIRST_c)]){
        QString users;
        foreach(Control *user,*item->getControl(Item::FIRST_c)){
            if(!users.contains(user->getUser()->getName())){
                users+= user->getUser()->getName();
                users+=',';
            }
        }

        ui->first_control->addItem(users);
        foreach(Control *reason,*item->getControl(Item::FIRST_c)){
            if(reason->getReason()!="") {ui->reason_first->setText(reason->getReason());break;}
        }
    }
    if(controls_valid[static_cast<int>(Item::SECOND_c)]){
        QString users;
        foreach(Control *user,*item->getControl(Item::SECOND_c)){
            if(!users.contains(user->getUser()->getName())){
                users+= user->getUser()->getName();
                users+=',';
            }
        }

        ui->second_control->addItem(users);
        foreach(Control *reason,*item->getControl(Item::SECOND_c)){
            if(reason->getReason()!="") {ui->reason_second->setText(reason->getReason());break;}
        }
    }

    virtual_dialog::setupTable();

    item_model_item *userM = new item_model_item(this,item,by_number);
    //Class for sorting items in the table
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(userM);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    for(int i = 0; i< ui->tableView->horizontalHeader()->count();i++){
        ui->tableView->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }

    if(by_number){
		//virtual_dialog_helper can be connected after intialization of table
        connect(ui->tableView->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(choose(QItemSelection,QItemSelection)));
	}
	else{
        connect(ui->tableView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(menuReq_wrapper(QPoint)));
        connect(this,SIGNAL(menuReq(QPoint)),this,SLOT(customMenu(QPoint)));
    }

    connect(ui->edit,SIGNAL(clicked(bool)),this,SLOT(edit(bool)));
    connect(ui->delete_2,SIGNAL(clicked(bool)),this,SLOT(remove(bool)));
}

void item_dialog::edit(bool){
    if(!by_number){
        ui->date_from_edit->setEnabled(true);
        ui->date_to_edit->setEnabled(true);
        ui->numberof->setEnabled(true);
        if(validScrew){
            ui->thread_current_edit->setEnabled(true);
            ui->thread_left_edit->setEnabled(true);
            ui->thread_right_edit->setEnabled(true);
        }
    }
    else{
        if(controls_valid[static_cast<int>(Item::FIRST_c)]){
            ui->reason_first->setEnabled(true);
        }
        if(controls_valid[static_cast<int>(Item::SECOND_c)]){
            ui->reason_second->setEnabled(true);
        }
    }
    ui->batch_edit->setEnabled(true);
    ui->number_edit->setEnabled(true);

    editMode=true;
}

void item_dialog::remove(bool){
    if(DialogBoxes::ConfBox("Do you really wnat to delete this order?")){
        if(!db.deleteItem(&listID.item_s)) DialogBoxes::ErrorBox("Error occured while saving");
        reloadMain(false);
        this->deleteLater();
    }
}

void item_dialog::closeEvent(QCloseEvent *e){
    if(editMode){
            State *state = new State(State::str2state(ui->state_edit->text()));
            User *user = new User(listID.user->getId(),listID.user->getName(),listID.user->getCardNumber());
            QDateTime time_from = QDateTime::fromString(ui->date_from_edit->text(),"dd.MM.yyyy HH:mm");
            QDateTime time_to = QDateTime::fromString(ui->date_to_edit->text(),"dd.MM.yyyy HH:mm");
            Item::Screw *screw = new Item::Screw(listID.screw_id,ui->thread_left_edit->currentText(),ui->thread_right_edit->currentText());
            QVector<Control*> control_first;
            QVector<Control*> control_second;

            if(ui->thread_current_edit->currentText()==UNKNOWN) screw->setC(Item::Screw::UNKNOW);
            else if(ui->thread_current_edit->currentText()==FIRST) screw->setC(Item::Screw::LEFT);
            else if(ui->thread_current_edit->currentText()==SECOND) screw->setC(Item::Screw::RIGHT);

            if(controls_valid[static_cast<int>(Item::FIRST_c)]){
                for(int i=0;i<listID.item_s.getControl(Item::FIRST_c)->size();i++){
                    Control* current = listID.item_s.getControl(Item::FIRST_c)->at(i);
                    User *id = new User(*current->getUser());
                    control_first.append(new Control(current->getID(),ui->batch_edit->text(),ui->number_edit->text(),id,Control::FIRST_c,current->getDateFrom()));
                    if(i==0) control_first.last()->setReason(ui->reason_first->text());
                    control_first.last()->setState(new State(*current->getState()));
                }
            }

            if(controls_valid[static_cast<int>(Item::SECOND_c)]){
                for(int i=0;i<listID.item_s.getControl(Item::SECOND_c)->size();i++){
                    Control* current = listID.item_s.getControl(Item::SECOND_c)->at(i);
                    User *id = new User(*current->getUser());
                    control_first.append(new Control(current->getID(),ui->batch_edit->text(),ui->number_edit->text(),id,Control::SECOND_c,current->getDateFrom()));
                    if(i==0) control_first.last()->setReason(ui->reason_first->text());
                    control_first.last()->setState(new State(*current->getState()));
                }
            }

            QRegExp re("\\d*");

            if(!by_number){
                if(time_from.isValid()&&state->isValid()&&re.exactMatch(ui->numberof->text())&&ui->number_edit->text()!=""&&ui->batch_edit->text()!=""){
                    Item item(time_from,state,listID.item_s.getID(),user,ui->batch_edit->text(),ui->number_edit->text());
                    item.setNumberOf(ui->numberof->text().toInt());
                    item.setScrew(screw);
                    item.setDateTo(time_to);

                    if(!db.saveItem(&item)) DialogBoxes::ErrorBox("Error occured while saving");

                    reloadMain(false);
                }
                else DialogBoxes::ErrorBox("Incorrect format of input data, changes weren't saved");
            }
            else{
                if(ui->batch_edit->text()!=""&&ui->number_edit->text()!=""){
                    foreach(Item *i,*items){
                        if(i->getNumber()==listID.item_s.getNumber()&&i->getBatch()==listID.item_s.getBatch()){
                            i->setBatch(ui->batch_edit->text());
                            i->setNumber(ui->number_edit->text());
                            if(!db.saveItem(i)) DialogBoxes::ErrorBox("Error occured while saving");
                        }
                    }

                    if(!control_first.empty()){
                        foreach(Control *c, control_first){
                            db.saveControl(c);
                            delete c;
                        }
                    }
                    if(!control_second.empty()){
                        foreach(Control *c, control_second){
                            db.saveControl(c);
                            delete c;
                        }
                    }

                    reloadMain(false);
                }
                else DialogBoxes::ErrorBox("Incorrect format of input data, changes weren't saved");
            }
    }

    virtual_dialog::closeEvent(e);
}

Item *item_dialog::overWrite(QDateTime from, QDateTime to, Item *item_t){
	/*
	 * 	Between model and view there is QSortFilterProxy, which translates indexs in table to 
	 * 	actual indexes in list, so we need to get pointer to model and not to QSortFilterProxy
	 * 	model
	 */
    Item *item_last=NULL;
    item_model_item *model = dynamic_cast<item_model_item*>(dynamic_cast<QSortFilterProxyModel*>(ui->tableView->model())->sourceModel());
    for(int i=0;i<ui->tableView->model()->rowCount();i++){
        QModelIndex index = ui->tableView->currentIndex();
        index=index.sibling(i,0);

        Item *item = model->data(index,item_model_item::internal_item).value<Item*>();
        if(item->getDateFrom()>=(from.addSecs(60))&&item->getDateFrom()<=(to.addSecs(-60))&&item->equal(item_t)
                &&item->getDateFrom()!=item_t->getDateFrom()){
            item_last=item;
            if(item->getType()==Item::ITEM){
                if(!db.deleteRecord(item)) DialogBoxes::ErrorBox("Chyba při ukládání dat");
            }
            else{
                if(!db.deleteRecord_c(dynamic_cast<Control*>(item))) DialogBoxes::ErrorBox("Chyba při ukládání dat");
            }
        }

        if(item->getDateFrom()>to) break;
    }
    return item_last;
}

Item *item_dialog::nextItem(Item *to,int row){
    item_model_item *model = dynamic_cast<item_model_item*>(dynamic_cast<QSortFilterProxyModel*>(ui->tableView->model())->sourceModel());
    if(row==-1){
        for(int i=0;i<ui->tableView->model()->rowCount();i++){
            QModelIndex index = ui->tableView->currentIndex();
            index=index.sibling(i,0);

            Item *item=model->data(index,item_model_item::internal_item).value<Item*>();

            if(item->getDateFrom()>to->getDateFrom()&&item->equal(to)){
                return item;
            }
        }
    }
    else{
        QModelIndex positionC = ui->tableView->currentIndex();
        positionC=positionC.sibling(row,0);
        return ui->tableView->model()->data(positionC,item_model_item::internal_item_next).value<Item*>();
    }
    return NULL;
}

Item *item_dialog::prevItem(Item* from,int row){
    item_model_item *model = dynamic_cast<item_model_item*>(dynamic_cast<QSortFilterProxyModel*>(ui->tableView->model())->sourceModel());
    if(row==-1){
        for(int i=ui->tableView->model()->rowCount()-1;i>=0;i--){
            QModelIndex index = ui->tableView->currentIndex();
            index=index.sibling(i,0);

            Item *item=model->data(index,item_model_item::internal_item).value<Item*>();

            if(item->getDateFrom()<from->getDateFrom()&&item->equal(from)){
                return item;
            }
        }
    }
    else{
        QModelIndex positionC = ui->tableView->currentIndex();
        positionC=positionC.sibling(row,0);
        return ui->tableView->model()->data(positionC,item_model_item::internal_item_prev).value<Item*>();
    }
    return NULL;
}

bool item_dialog::append(bool New){
    QDialog q;
    Ui::state_ch ui_d;
    QModelIndex positionC = ui->tableView->currentIndex();

    Item empty;
    empty.setID(listID.item_s.getID());

    Item *item=&empty;
    Item *nextI=&empty;

    ui_d.setupUi(&q);
    q.setWindowIcon(QIcon(":/new/prefix1/icon.png"));
    if(New){
        q.setWindowTitle("New state");
        ui_d.label->setText("New state:");
    }
    else{
        q.setWindowTitle("Edit");
        nextI = nextItem(NULL,positionC.row());
        item = ui->tableView->model()->data(positionC,item_model_item::internal_item).value<Item*>();

        if(nextI==NULL) nextI=&empty;
    }

    QMap<QString,Item::TYPE_CLASS> map_type;
    QMap<Item::TYPE_CLASS,QString> map_type_rev;
    QMap<QString,Control::COUNT> map_control_type;
    map_type["Rolling"]=Item::ITEM;
    map_type["Control"]=Item::CONTROL;
    map_control_type["First"]=Control::FIRST_c;
    map_control_type["Second"]=Control::SECOND_c;
    map_type_rev[map_type["Rolling"]]="Rolling";
    map_type_rev[map_type["Control"]]="Control";

	//disables to date if state is completed, because this state has no duration
    connect(ui_d.state,&QComboBox::currentTextChanged,this,[ui_d,map_type_rev](QString text){
        if(State::str2state(text)==State::completed){
            ui_d.do_2->setEnabled(false);
        }
        else if(State::str2state(text)==State::stopped&&ui_d.type->currentText()==map_type_rev[Item::CONTROL]){
            ui_d.do_2->setEnabled(false);
        }
        else ui_d.do_2->setEnabled(true);
    });

	//disables type and user if object is control because these properties are
	//inherited from item
    connect(ui_d.type,&QComboBox::currentTextChanged,this,[ui_d,map_type_rev,New](QString text){
        if(text==map_type_rev[Item::CONTROL]){
            ui_d.type_c->setEnabled(true);
            if(New)ui_d.user->setEnabled(true);
        }
        else{
            ui_d.user->setEnabled(false);
            ui_d.type_c->setEnabled(false);
        }
        ui_d.state->currentTextChanged(ui_d.state->currentText());
    });

	//initialization of combo boxes
    for(int i=0;i<STATE_SIZES;i++) ui_d.state->addItem(State::choises[i]);
    ui_d.type_c->addItem(map_control_type.key(Control::FIRST_c));
    ui_d.type_c->addItem(map_control_type.key(Control::SECOND_c));
    ui_d.type->addItem(map_type_rev[Item::ITEM]);
    ui_d.type->addItem(map_type_rev[Item::CONTROL]);

    if(New){
        ui_d.od->setDateTime(QDateTime::currentDateTime());
        ui_d.do_2->setDateTime(QDateTime::currentDateTime());
        ui_d.state->setCurrentIndex(1);

        foreach(User *u,*listID.users) ui_d.user->addItem(u->getName());
    }
    else{
        ui_d.od->setDateTime(item->getDateFrom());
        ui_d.do_2->setDateTime(nextI->getDateFrom().isValid() ? nextI->getDateFrom() : QDateTime::currentDateTime());
        ui_d.state->setCurrentText(item->getState()->toString());
        if(*item->getState()==State(State::completed)||
                (item->getType()==Item::CONTROL&&*item->getState()==State(State::stopped))) ui_d.do_2->setEnabled(false);
        ui_d.type->setCurrentText(map_type_rev[item->getType()]);
        ui_d.type->setDisabled(true);
        ui_d.type_c->setDisabled(true);
        ui_d.user->setDisabled(true);

        ui_d.user->addItem(item->getUser()->getName());
    }

	//displays dialog
    if(q.exec()){
         QDateTime from = ui_d.od->dateTime();
         QDateTime to = ui_d.do_2->dateTime();
         State *state = new State(State::str2state(ui_d.state->currentText()));
         qDebug()<<ui_d.state->currentText();

         if(from>=to){
             DialogBoxes::ErrorBox("To cannot be before from");
             return false;
         }

		 //function that saves item based on it's type
         auto helper_f = [this](Item* item) -> bool{
            if(item->getType()==Item::ITEM) return db.saveRecord(item);
            else{
                return db.saveControl_h(dynamic_cast<Control*>(item));
            }
         };


         if(New){
             User *user = new User(*listID.user);
             const QVector<Control*> *control_id = map_control_type[ui_d.type_c->currentText()]==Control::FIRST_c ?
                         listID.item_s.getControl(Item::FIRST_c) : listID.item_s.getControl(Item::SECOND_c);

             if(map_type[ui_d.type->currentText()]==Item::CONTROL&&control_id->empty()){
                 DialogBoxes::ErrorBox("This order has no "+ui_d.type_c->currentText()+" control yet");
                 return false;
             }else if(map_type[ui_d.type->currentText()]==Item::CONTROL){
                 foreach(User *u,*listID.users){
                     if(u->getName()==ui_d.user->currentText()){user=u;break;}
                 }
             }

             item = map_type[ui_d.type->currentText()]==Item::ITEM ?
                         new Item(from,state,listID.item_s.getID(),user,0,0) :
                         new Control(control_id->first()->getID(),0,0,user,
                                     map_control_type[ui_d.type_c->currentText()],from);
             if(item->getType()==Item::CONTROL) item->setState(state);
             item->setDateTo(from);

             item->setDateFrom(to);
             nextI = nextItem(item);
             item->setDateFrom(from);
             if(nextI==NULL) nextI=&empty;

         }
         else{
            item->setDateTo(from);
            item->setState(state);
         }

         Item *item_next = overWrite(from,to,item);
         if(item_next==NULL) item_next=&empty;

         Item *prev_item = prevItem(item,New ? -1 : positionC.row());
         if(prev_item==NULL) prev_item=&empty;

		/*
		 * Sections that handles logic behind changing states history
		 *
		 * TODO: needs complete rewriting
		 */

         if(state->getState()!=State::completed&&
                 (item->getType()==Item::ITEM||state->getState()!=State::stopped)){
            if(item_next->getDateFrom().isValid()){
                qDebug()<<"overwrite";
                item_next->setDateTo(to);
                if(!helper_f(item_next)) DialogBoxes::ErrorBox("Error occured, while saving.");
            }
            else if(nextI->getDateFrom().isValid()){
                qDebug()<<"after me";
                nextI->setDateTo(to);
                if(!helper_f(nextI)) DialogBoxes::ErrorBox("Error occured, while saving.");
            }
            else if(New&&prev_item->getDateFrom().isValid()){
                qDebug()<<"before me";
                prev_item->setDateTo(to);
                prev_item->setDateFrom(to);
                if(!helper_f(prev_item)) DialogBoxes::ErrorBox("Error occured, while saving.");
            }
         }
         if(!helper_f(item)) DialogBoxes::ErrorBox("Error occured, while saving.");

         if(New) delete item;
         disconnect(ui_d.state,SIGNAL(currentIndexChanged(QString)));
         return true;
    }
    else{
        disconnect(ui_d.state,SIGNAL(currentIndexChanged(QString)));
        return false;
    }
}

void item_dialog::reloadModel(){
    delete (dynamic_cast<QSortFilterProxyModel*>(ui->tableView->model()))->sourceModel();
    delete ui->tableView->model();

    item_model_item *userM = new item_model_item(this,&listID.item_s,by_number);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(userM);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
}

//appear on right click on state's history record
void item_dialog::customMenu(QPoint position){
    qDebug()<<position;
    QMenu menu(this);

    QAction *u = menu.addAction("Edit");
    QAction *n = menu.addAction("Add");
    QAction *d = menu.addAction("Delete");
    QAction *a = menu.exec(ui->tableView->viewport()->mapToGlobal(position));

    QModelIndex positionC = ui->tableView->currentIndex();
    bool changed = false;

    if(positionC.row()!=-1){
        Item *toTest = ui->tableView->model()->data(positionC,item_model_item::internal_item).value<Item*>();

		//in case when states are displayed by batch number context menu isn't 
		//available 
        if(toTest->getType()==Item::ITEM&&by_number) return;
    }

    if(a==u&&positionC.row()!=-1){
        if(append()){
            reloadModel();
            changed=true;
        }

    }
    if(a==n&&(positionC.row()!=-1||ui->tableView->model()->rowCount()==0)){
        if(append(true)){
            reloadModel();
            changed=true;
        }
    }
    if(a==d&&positionC.row()!=-1){
        if(DialogBoxes::ConfBox("Do you really want to delete this record ?")){
            Item *item = ui->tableView->model()->data(positionC,item_model_item::internal_item).value<Item*>();
            if(item->getType()==Item::ITEM) db.deleteRecord(item);
            else db.deleteRecord_c(dynamic_cast<Control*>(item));
            reloadModel();
            changed=true;
        }
    }

    if(changed){
        item_model_item *model = dynamic_cast<item_model_item*>(dynamic_cast<QSortFilterProxyModel*>(ui->tableView->model())->sourceModel());
        positionC = ui->tableView->indexAt(QPoint(0,0));

        Item item = Item(listID.item_s);

        bool item_finded = by_number ? true : false;
        bool control_first_finded = by_number ? false : true;
        bool control_second_finded = by_number ? false : true;
        for(int i=model->rowCount()-1;i>=0;i--){
            Item *item_c = model->data(positionC.sibling(i,0),item_model_item::internal_item).value<Item*>();
            if(item_c->getType()==Item::ITEM&&!item_finded){
                item_finded=true;
                item.setState(new State(*item_c->getState()));
                if(!db.saveItem(&item)) DialogBoxes::ErrorBox("Error occured, while saving.");
            }
            else if(item_c->getType()==Item::CONTROL){
                Control *con = db.loadControl(item_c->getID()); 
                if(!controls_valid[0]) control_first_finded=true;
                if(!controls_valid[1]) control_second_finded=true;

                if(con->getCount()==Control::COUNT::FIRST_c&&!control_first_finded){
                    con->setState(new State(*item_c->getState()));
                    if(!db.saveControl(con)) DialogBoxes::ErrorBox("Error occured, while saving.");
                    control_first_finded=true;
                }
                if(con->getCount()==Control::COUNT::SECOND_c&&!control_second_finded){
                    con->setState(new State(*item_c->getState()));
                    if(!db.saveControl(con)) DialogBoxes::ErrorBox("Error occured, while saving.");
                    control_second_finded=true;
                }
                delete con;
            }

           if(item_finded&&control_first_finded&&control_second_finded) break;
        }
    }
}

item_dialog::~item_dialog(){
    disconnect(ui->tableView->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)));
    disconnect(ui->tableView,SIGNAL(customContextMenuRequested(QPoint)));
    disconnect(ui->edit,SIGNAL(clicked(bool)));
    disconnect(ui->delete_2,SIGNAL(clicked(bool)));

    delete (dynamic_cast<QSortFilterProxyModel*>(ui->tableView->model()))->sourceModel();
    delete ui->tableView->model();
    delete ui;
}
