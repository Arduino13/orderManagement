#include "database_obj.h"

database_obj::database_obj()
{
    type2str[type::USER]="users";
    type2str[type::RECORD]="records";
    type2str[type::HISTORY_R]="history_rec";
    type2str[type::CONF]="setting";
    type2str[type::SCREW]="items";
    type2str[type::CONTROL]="controls";
    type2str[type::HISTORY_C]="history_con";

    num2str_c[Control::FIRST_c]="FIRST";
    num2str_c[Control::SECOND_c]="SECOND";
    num2str_c[Control::UNKNOW_c]="UNKNOWN";

    QDateTime date = QDateTime::fromString("2010-10-25T10:28:58.570Z", "yyyy-MM-ddTHH:mm:ss.zzzZ");
    date.setTimeSpec(Qt::UTC);
    QDateTime local = date.toLocalTime();
    date.setTimeSpec(Qt::LocalTime);

    timeOffset=date.secsTo(local);
}

Database* database_obj::open(){
    return new Database(name_db,name,pass);
}

bool database_obj::TestIt(QSqlQuery *rs){
    if(!rs->next()) return false;
    else return true;
}

bool database_obj::saveItem(const Item *to_save){
    Database *db = open();

    if(to_save->getDateFrom().isNull()||to_save->getState()==NULL||to_save->getUser()==NULL||to_save->getID()==NULL){
        throw new exception("Object is inconsistent");
    }

    bool New = !exist(type::RECORD,to_save->getID());

    bool to_return;
    bool screw_return;

    QString screwId = to_save->getScrew()==NULL ? NULL : to_save->getScrew()->getId();

	//saving thread's type
    if(screwId!=NULL) screw_return=threadSave(to_save->getScrew());
    else screw_return=true;

    QDateTime date_to = to_save->getDateTo();
    if(date_to.isValid()) date_to.addSecs(0-timeOffset);

    if(New){
        QVector<QVariant> params({to_save->getID(),to_save->getDateFrom().addSecs(0-timeOffset),date_to,to_save->getUser()->getId(),
                                 to_save->getState()->getState(),to_save->getBatch(),to_save->getNumber(),screwId,to_save->getNumberOf()});
        to_return = db->insert(type2str[type::RECORD],&params);
        delete db;
    }
    else{
        QVector<QString> columns({"date_from","date_to","user_id","state","batch","number","screw","number_of"});
        QVector<QVariant> params({to_save->getDateFrom().addSecs(0-timeOffset),date_to,to_save->getUser()->getId(),
                                 to_save->getState()->getState(),to_save->getBatch(),to_save->getNumber(),screwId,to_save->getNumberOf(),to_save->getID()});
        to_return = db->update(type2str[type::RECORD],&columns,"id=?",&params);
        delete db;
    }
    if(!to_return||!screw_return) return false;
    else return true;
}

bool database_obj::saveUser(const User *to_save){
    Database *db = open();
    bool New = !exist(type::USER,to_save->getId());

    if(to_save->getCardNumber()==NULL||to_save->getName()==NULL||to_save->getId()==NULL){
        throw new exception("Object is inconsistent");
    }

	if(New){
        QVector<QVariant> params({to_save->getId(),to_save->getCardNumber(),to_save->getName()});
        bool to_return = db->insert(type2str[type::USER],&params);
        delete db;
        return to_return;
    }
    else{
        QVector<QString> columns({"card_number","name"});
        QVector<QVariant> params({to_save->getCardNumber(),to_save->getName(),to_save->getId()});
        bool to_return = db->update(type2str[type::USER],&columns,"id=?",&params);
        delete db;
        return to_return;
    }
}

bool database_obj::saveControl(const Control *control){
    Database *db = open();
    bool New = !exist(type::CONTROL,control->getID());
    bool to_return = false;

    if(control->getDateFrom().isNull()||control->getState()==NULL||control->getUser()==NULL||control->getID()==NULL){
        throw new exception("Object is inconsistent");
    }

    QDateTime date_to = control->getDateTo();
    if(date_to.isValid()) date_to.addSecs(0-timeOffset);

    if(New){
        QVector<QVariant> params({control->getID(),control->getDateFrom().addSecs(0-timeOffset),date_to,control->getUser()->getId(),
                                 control->getState()->getState(),control->getBatch(),control->getNumber(),control->getNumberOf(),
                                  num2str_c[control->getCount()],control->getReason()});
        to_return = db->insert(type2str[type::CONTROL],&params);
        delete db;
    }
    else{
        QVector<QString> columns({"date_from","date_to","user_id","state","batch","number","number_of","count","reason"});
        QVector<QVariant> params({control->getDateFrom().addSecs(0-timeOffset),date_to,control->getUser()->getId(),
                                 control->getState()->getState(),control->getBatch(),control->getNumber(),control->getNumberOf(),
                                  num2str_c[control->getCount()],control->getReason(),control->getID()});
        to_return = db->update(type2str[type::CONTROL],&columns,"id=?",&params);
        delete db;
    }

    return to_return;
}

User* database_obj::loadUser(const QString id, QSqlRecord rec){
    bool NewData = rec.isEmpty();

    Database *db=NULL;
    if(NewData) db=open();

    QVector<QString> obj({"*"});
    QVector<QString> target ({id});

    QSqlQuery *query=NULL;
    QSqlRecord record;
    QSqlRecord *rs=&record;
    if(NewData){
        query=db->select(type2str[type::USER],&obj,"id=?",&target);
        query->next();
        record=query->record();
    }
    else record=rec;

    if(rs->isEmpty()){
        throw new exception("user does not exist");
    }

    QString id_user = rs->value("id").toString();
    QString cardNumber = rs->value("card_number").toString();
    QString name = rs->value("name").toString();

    if(NewData){
        delete query;
        delete db;
    }

    return new User(id_user,name,cardNumber);
}

Item* database_obj::loadItem(const QString id, QSqlRecord rec, QSqlRecord rec_u, QSqlRecord rec_s){
    bool NewData = rec.isEmpty();

    Database *db=NULL;
    if(NewData) db=open();

    QVector<QString> obj({"*"});
    QVector<QString> target ({id});

    QSqlQuery *tempQuery=NULL;
    QSqlRecord record;
    QSqlRecord *rs = &record;
    if(NewData){
        tempQuery=db->select(type2str[type::RECORD],&obj,"id=?",&target);
        tempQuery->next();
        record=tempQuery->record();
    }
    else{
        record=rec;
    }


    if(rs->isEmpty()) throw new exception("item does not exist");

    QString id_item = rs->value("id").toString();
    QDateTime date_from = rs->value("date_from").toDateTime().addSecs(timeOffset);
    QDateTime date_to = rs->value("date_to").toDateTime();
    QString userId = rs->value("user_id").toString();
    State *state = new State(rs->value("state").toInt());
    QString batch = rs->value("batch").toString();
    QString number = rs->value("number").toString();
    QString screw = rs->value("screw").toString();
    int numberOf = rs->value("number_of").toInt();

    Item *New = new Item(date_from,state,id_item,loadUser(userId,rec_u),batch,number);
    if(!date_to.isNull()) New->setDateTo(rs->value("date_to").toDateTime().addSecs(timeOffset));

    if(NewData){
        delete tempQuery;
        delete db;
    }

	//loading item's thread
    if(screw!=NULL) New->setScrew(threadLoad(screw,rec_s));

    New->setNumberOf(numberOf);

    if(New->getUser()!=NULL) return New;
    else return NULL;
}

Control* database_obj::loadControl(const QString id, QSqlRecord rec, QSqlRecord rec_u){
    bool NewData = rec.isEmpty();

    Database *db=NULL;
    if(NewData) db=open();

    QVector<QString> obj({"*"});
    QVector<QString> target ({id});

    QSqlQuery *tempQuery=NULL;
    QSqlRecord record;
    QSqlRecord *rs = &record;
    if(NewData){
        tempQuery=db->select(type2str[type::CONTROL],&obj,"id=?",&target);
        tempQuery->next();
        record=tempQuery->record();
    }
    else{
        record=rec;
    }


    if(rs->isEmpty()) throw new exception("item does not exist");

    QString id_item = rs->value("id").toString();
    QDateTime date_from = rs->value("date_from").toDateTime().addSecs(timeOffset);
    QDateTime date_to = rs->value("date_to").toDateTime();
    QString userId = rs->value("user_id").toString();
    State *state = new State(rs->value("state").toInt());
    QString batch = rs->value("batch").toString();
    QString number = rs->value("number").toString();
    int number_of = rs->value("number_of").toInt();

    QMap<QString,Control::COUNT> reverse;
    reverse[num2str_c[Control::FIRST_c]]=Control::FIRST_c;
    reverse[num2str_c[Control::SECOND_c]]=Control::SECOND_c;
    reverse[num2str_c[Control::UNKNOW_c]]=Control::UNKNOW_c;

    Control::COUNT count = reverse[rs->value("count").toString()];
    QString reason = rs->value("reason").toString();

    Control *New = new Control(id_item,batch,number,loadUser(userId,rec_u),count,date_from);
    New->setState(state);
    New->setNumberOf(number_of);
    if(reason!="") New->setReason(reason);

    if(!date_to.isNull()) New->setDateTo(rs->value("date_to").toDateTime().addSecs(timeOffset));

    if(NewData){
        delete tempQuery;
        delete db;
    }

    if(New->getUser()!=NULL) return New;
    else return NULL;
}

QVector<User*>* database_obj::loadListUser(){
    Database *db = open();
    QVector<QString> obj({"*"});
    QVector<User*> *to_return = new QVector<User*>();

    QSqlQuery *list = db->select<int>(type2str[type::USER], &obj, NULL);
    //prekladac nezjisti z null typename pro sablonu musi se zadat nejaky typ explicitne

    while(list->next()){
        to_return->append(loadUser(list->value("id").toString(),list->record()));
    }

    delete list;
    delete db;

    return to_return;
}
QVector<Control*>* database_obj::loadListControl(int limit, int index){
    Database *db = open();
    QVector<QString> obj({"*"});
    QVector<Control*> *to_return = new QVector<Control*>();

    QSqlQuery *list = db->select<int>(type2str[type::CONTROL], &obj, NULL);
    QSqlQuery *user_list = db->select<int>(type2str[type::USER], &obj, NULL);

    int counter=0;
    int loaded=0;
    while(list->next()){
        if(counter>=index){
            QSqlRecord user;

            for(int i=0;i<user_list->size();i++){
                user_list->seek(i);
                if(user_list->value("id")==list->value("user_id")) user=user_list->record();
            }

            to_return->append(loadControl(list->value("id").toString(),list->record(),user));
            loaded++;
        }

        if(limit>0&&loaded>=limit) break;
        counter++;
    }

    delete list;
    delete user_list;
    delete db;

    return to_return;
}

QVector<Item*>* database_obj::loadListItem(int limit, int index){
    Database *db = open();
    QVector<QString> obj({"*"});
    QVector<Item*> *to_return = new QVector<Item*>();

    QSqlQuery *list = db->select<int>(type2str[type::RECORD], &obj, NULL);
    QSqlQuery *screw_list = db->select<int>(type2str[type::SCREW], &obj, NULL);
    QSqlQuery *user_list = db->select<int>(type2str[type::USER], &obj, NULL);

    int counter=0;
    int loaded=0;
    while(list->next()){
        if(counter>=index){
            QSqlRecord user;
            QSqlRecord screw;

            for(int i=0;i<user_list->size();i++){
                user_list->seek(i);
                if(user_list->value("id")==list->value("user_id")) user=user_list->record();
            }

            for(int i=0;i<screw_list->size();i++){
                screw_list->seek(i);
                if(screw_list->value("id")==list->value("screw")) screw=screw_list->record();
            }

            to_return->append(loadItem(list->value("id").toString(),list->record(),user,screw));
            loaded++;
        }

        if(limit>0&&loaded>=limit) break;
        counter++;
    }

    delete list;
    delete user_list;
    delete screw_list;
    delete db;

    return to_return;
}

QVector<Item*>* database_obj::loadHistory(const QString id, QVector<User *> *u_temp, int, int, const type what){
    QVector<User*>* users = u_temp==NULL ? loadListUser() : u_temp;
    Database *db = open();
    QVector<QString> obj({"*"});
    QVector<QString> target({id});
    QVector<Item*> *to_return = new QVector<Item*>();

    QSqlQuery *list = db->select(type2str[what],&obj,"id=?",&target);

    while(list->next()){
        QDateTime time = list->value("date").toDateTime().addSecs(timeOffset);
        QString id = list->value("id").toString();
        State *state = new State(list->value("state").toInt());
        QString id_u = list->value("user_id").toString();
        User *user=NULL;
        foreach(User *u,*users){
            if(id_u==u->getId()) user=new User(*u);
        }

        to_return->append(new Item(time,state,id,user,0,0));
    }

    delete list;
    if(u_temp==NULL) delete users;
    delete db;

    return to_return;
}

QVector<Item*>* database_obj::loadHistory(const QString id, QVector<User *> *u_temp, int limit, int index){
    return loadHistory(id,u_temp,limit,index,HISTORY_R);
}

QVector<Item*>* database_obj::loadHistory_c(const QString id, QVector<User *> *u_temp, int limit, int index){
    QVector<Item*>* list = loadHistory(id,u_temp,limit,index,HISTORY_C);
    QVector<Item*>* to_return = new QVector<Item*>();

    foreach(Item *i, *list){
        Control *control = new Control(i->getID(),0,0,new User(*i->getUser()),Control::FIRST_c,i->getDateFrom());
        to_return->append(control);
        control->setState(new State(*i->getState()));
        delete i;
    }
    delete list;
    return to_return;
}

QVector<Item*>* database_obj::loadHistory(const QString id, const QString number,const QString batch, int limit, int index, getter_f function){
    if(id==NULL){
        QVector<Item*>* history = new QVector<Item*>();
        QVector<Item*>* list_temp=NULL; 
        QVector<User*>* u_temp = loadListUser();
        bool Del = false;

        if(list_temp==NULL){
            list_temp=this->loadListItem();
            foreach(Control *c,*loadListControl()){
                list_temp->append(c);
            }

            Del=true;
        }

        foreach(Item* i,*list_temp){
            if(i->getNumber()==number&&i->getBatch()==batch){
                QVector<Item*>* temp=function(i->getID(),u_temp,i,limit,index);
                if(temp!=NULL){
                    *history+=*temp;
                    delete temp;
                }
            }
        }

        if(Del){
            foreach(Item* i,*list_temp) delete i;
            delete list_temp;
        }
        foreach(User *u,*u_temp) delete u;
        delete u_temp;

        return history;
    }
    else return function(id,NULL,NULL,limit,index);
}

QVector<Item*>* database_obj::loadHistory(const QString id, const QString number, const QString batch, const QVector<Item *> *){
    database_obj *myself = this;
    return loadHistory(id,number,batch,0,0,getter_f(
                       [myself] (const QString s,QVector<User*>* u,Item *item,int i,int l) -> QVector<Item*>* {
                                if(item==NULL||item->getType()==Item::ITEM) return myself->loadHistory(s,u,i,l);
                                else return NULL;
                            })
                       );
}

QVector<Control*>* database_obj::loadHistory_c(const QString id, const QString number, const QString batch, const QVector<Control *> *){
    database_obj *myself = this;

    QVector<Control*>* to_return = new QVector<Control*>();
    QVector<Item*>* list = loadHistory(id,number,batch,0,0,getter_f(
                                           [myself] (const QString s,QVector<User*>* u,Item *item,int i,int l) -> QVector<Item*>* {
                                                if(item==NULL||item->getType()==Item::CONTROL) return myself->loadHistory_c(s,u,i,l);
                                                else return NULL;
                                            })
                                       );

    foreach(Item *i,*list){
        to_return->append(dynamic_cast<Control*>(i));
    }
    delete list;

    return to_return;
}

void database_obj::loadControlsTo(QVector<Item *> *list){
    QVector<Control*>* listC = loadListControl();
    QVector<Item*> listI = *list;

    std::sort(listI.begin(),listI.end(),Item::sortDate);

    foreach(Item *i,listI){
        foreach(Control *c,*listC){
            if(i->getNumber()==c->getNumber()&&i->getBatch()==c->getBatch()){
                i->setControl(c);
            }
        }
    }

    delete listC;
}

bool database_obj::saveRecord(const Item *item,const type what){
    Database *db = open();
    bool New = !exist(what,item->getDateFrom().addSecs(0-timeOffset).toString("yyyy-MM-dd HH:mm:ss"));

    if(!item->getDateFrom().isValid()||!item->getDateTo().isValid()||item->getID()==""||item->getState()->getState()==State::unknown){
        throw new exception("history record is non consistent");
    }

    QDateTime date_to = item->getDateTo().addSecs(0-timeOffset);
    QDateTime date_from = item->getDateFrom().addSecs(0-timeOffset);

    if(New){
        QVector<QVariant> param ({item->getID(),date_to.toString("yyyy-MM-dd HH:mm:ss"),item->getUser()->getId(),item->getState()->getState()});
        bool to_return = db->insert(type2str[what],&param);
        delete db;
        return to_return;
    }
    else{
        QVector<QVariant> param ({item->getID(),date_to.toString("yyyy-MM-dd HH:mm:ss"),
                                  item->getUser()->getId(),item->getState()->getState(),date_from.toString("yyyy-MM-dd HH:mm:ss")});
        QVector<QString> columns ({"id","date","user_id","state"});
        bool to_return = db->update(type2str[what],&columns,"date=?",&param);
        delete db;
        return to_return;
    }
}

bool database_obj::saveControl_h(const Control* control){
    return saveRecord(control,type::HISTORY_C);
}

bool database_obj::saveRecord(const Item *item){
    return saveRecord(item,type::HISTORY_R);
}

bool database_obj::deleteItem(const Item *item){
    Database *db = open();
    QVector<QString> param({item->getID()});

    bool to_return = db->remove(type2str[type::RECORD],"id=?",&param);
    delete db;

    return to_return;
}

bool database_obj::deleteUser(const User *item){
    Database *db = open();
    QVector<QString> param({item->getId()});

    bool to_return = db->remove(type2str[type::USER],"id=?",&param);
    delete db;

    return to_return;
}

bool database_obj::deleteRecord(const Item *item){
    Database *db = open();
    QVector<QString> param({item->getDateFrom().addSecs(0-timeOffset).toString("yyyy-MM-dd HH:mm:ss")});

    bool to_return = db->remove(type2str[type::HISTORY_R],"date=?",&param);
    delete db;

    return to_return;
}

bool database_obj::deleteHistory(){
    Database *db = open();

    bool to_return = db->remove<int>(type2str[type::HISTORY_R],"",NULL);
    to_return = db->remove<int>(type2str[type::HISTORY_C],"",NULL);

    delete db;
    return to_return;
}

QString database_obj::confLoad(const QString id){
    Database *db = open();

    QVector<QString> params({id});
    QVector<QString> obj({"*"});

    QSqlQuery *rs = db->select(type2str[type::CONF],&obj,"id=?",&params);

    rs->next();
    QString to_return = rs->value("value").toString();

    delete rs;
    delete db;

    return to_return;
}

bool database_obj::threadSave(const Item::Screw *item){
    QString id = item->getId();
    QString number = item->getNumber();
    QString left = item->getT(Item::Screw::screw_t::LEFT);
    QString right = item->getT(Item::Screw::screw_t::RIGHT);
    QString current = item->getC()==Item::Screw::screw_t::LEFT ? "first" : "second";

    if(item->getC()==Item::Screw::screw_t::UNKNOW) current=QString::null;

    Database *db = open();
    bool New = !exist(type::SCREW,id);

    if(New){
        QVector<QVariant> params({id,number,left,right,current});
        bool to_return=db->insert(type2str[type::SCREW],&params);
        delete db;
        return to_return;
    }
    else{
        QVector<QVariant> params({number,left,right,current,id});
        QVector<QString> columns({"number","type_thread_l", "type_thread_r","current"});

        bool to_return = db->update(type2str[type::SCREW],&columns,"id=?",&params);
        delete db;
        return to_return;
    }
}

Item::Screw* database_obj::threadLoad(const QString id, QSqlRecord rec){
    bool NewData = rec.isEmpty();

    Database *db=NULL;
    if(NewData) db=open();

    QVector<QString> columns({"*"});
    QVector<QString> target({id});

    QSqlQuery *query=NULL;
    QSqlRecord record;
    QSqlRecord *rs=&record;
    if(NewData){
        query=db->select(type2str[type::SCREW],&columns,"id=?",&target);
        query->next();
        record=query->record();
    }
    else record=rec;

    if(rs->isEmpty()) throw new exception("thread does not exist");

    QString left_t = rs->value("type_thread_l").toString();
    QString right_t = rs->value("type_thread_r").toString();
    Item::Screw::screw_t current = rs->value("current").toString()=="first" ? Item::Screw::screw_t::LEFT : Item::Screw::screw_t::RIGHT;
    if(rs->value("current").isNull()) current=Item::Screw::screw_t::UNKNOW;

    Item::Screw *screw = new Item::Screw(id,left_t,right_t,current);
    if(NewData){
        delete query;
        delete db;
    }

    return screw;
}

bool database_obj::confSave(const QString id, const QString conf){
    Database *db = open();
    bool New = !exist(type::CONF,id);

    if(New){
        QVector<QString> params({id,conf});
        bool to_return = db->insert(type2str[type::CONF],&params);
        delete db;
        return to_return;
    }
    else{
        QVector<QString> params({conf,id});
        QVector<QString> columns({"value"});
        bool to_return = db->update(type2str[type::CONF],&columns,"id=?",&params);
        delete db;
        return to_return;
    }
}

bool database_obj::deleteConf(const QString id){
    Database *db = open();
    QVector<QString> param({id});

    bool to_return = db->remove(type2str[type::CONF],"id=?",&param);
    delete db;

    return to_return;
}

bool database_obj::deleteScrew(const Item::Screw *screw){
    Database *db = open();
    QVector<QString> param({screw->getId()});

    bool to_return = db->remove(type2str[type::SCREW],"id=?",&param);
    delete db;
    return to_return;
}

bool database_obj::deleteControl(const Control *control){
    Database *db = open();
    QVector<QString> param({control->getID()});

    bool to_return = db->remove(type2str[type::CONTROL],"id=?",&param);
    delete db;
    return to_return;
}

bool database_obj::deleteRecord_c(const Control *control){
    Database *db = open();
    QVector<QString> param({control->getDateFrom().addSecs(0-timeOffset).toString("yyyy-MM-dd HH:mm:ss")});

    bool to_return = db->remove(type2str[type::HISTORY_C],"date=?",&param);
    delete db;
    return to_return;
}
