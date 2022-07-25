#include "item_model_item.h"

const int item_model_item::internal_id=255;
const int item_model_item::internal_item=256;
const int item_model_item::internal_item_next=257;
const int item_model_item::internal_item_prev=258;

item_model_item::item_model_item(QObject *parent, const Item *item, bool by_number) : QAbstractTableModel(parent)
{   
    this->by_number=by_number;
    this->item=*item;
    reloadData();
}

void item_model_item::reloadData(){
    if(history!=NULL){
        foreach(Item *i,*history) delete i;
        delete history;
    }

    if(!by_number){
        history = db.loadHistory(item.getID(),NULL,NULL);
        foreach(Control *s,*db.loadHistory_c(NULL,item.getNumber(),item.getBatch())){
            if(*s->getUser()==*item.getUser()) history->append(s);
        }
    }
    else{
        history = db.loadHistory(NULL,item.getNumber(),item.getBatch());
        foreach(Control *s,*db.loadHistory_c(NULL,item.getNumber(),item.getBatch())){
            history->append(s);
        }
    }

    std::sort(history->begin(),history->end(),Item::sortDate);
}

int item_model_item::rowCount(const QModelIndex &) const{
    return history->size();
}

int item_model_item::columnCount(const QModelIndex &) const{
    return by_number ? COLUM_NUM_ITEM_EXTEND : COLUM_NUM_ITEM;
}

QVariant item_model_item::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role==Qt::DisplayRole&&orientation==Qt::Horizontal){
        switch(section){
            case DATE_FROM:
                return QString("From");
            case DATE_TO:
                return QString("To");
            case DURATION:
                return QString("Duration");
            case STATE:
                return QString("State");
            case TYPE:
                return QString("Action");
            case USER:
                return QString("User");
            case COUNT_C:
                return QString("Type");
        }
    }
    return QVariant();
}

QVariant item_model_item::data(const QModelIndex &index, int role) const{
    int row = index.row();
    COLUMS colum = static_cast<COLUMS>(index.column());

    if(history!=NULL&&history->size()>0){
        Item *currentOne = history->at(row);
        Item *nextOne = NULL;
        foreach(Item *i,* history){
            if(i->equal(currentOne)
                    &&currentOne!=i
                    &&i->getDateFrom().secsTo(currentOne->getDateFrom())<=0){
                nextOne=i;
                break;
            }
        }
        switch(role){
            case Qt::DisplayRole:
                switch(static_cast<int>(colum)){
                    case DATE_FROM:
                        return currentOne->getDateFrom();
                    case DATE_TO:
                        if(*currentOne->getState()==State(State::completed)||
                            (currentOne->getType()==Item::CONTROL&&*currentOne->getState()==State(State::stopped))) return currentOne->getDateFrom();
                        else if(nextOne!=NULL) return nextOne->getDateFrom();
                        else return QString("");
                    case DURATION:{
                        QDateTime to;
                        if(*currentOne->getState()==State(State::completed)||
                                (currentOne->getType()==Item::CONTROL&&*currentOne->getState()==State(State::stopped))) to=currentOne->getDateFrom();
                        else if(nextOne!=NULL) to = nextOne->getDateFrom();
                        else to=QDateTime::currentDateTime();

                        qint64 time = currentOne->getDateFrom().secsTo(to);

                        int days=0;
                        int hours=0;
                        int minutes=0;

                        if(time>=(60*60*24)){
                            days=time/(60*60*24);
                            time-=(days*(60*60*24));
                        }
                        if(time>=(60*60)){
                            hours=time/(60*60);
                            time-=(hours*(60*60));
                        }
                        minutes=time/60;

                        return QString("dd: "+QString::number(days)+" hh: "+QString::number(hours)+" mm: "+QString::number(minutes));
                }
                    case STATE:
                        return currentOne->getState()->toString();
                    case TYPE:
                            if(currentOne->getType()==Item::ITEM) return QString("Rolling");
                            else return QString("Control");
                            break;
                    case USER:
                        return currentOne->getUser()->getName();
                    case COUNT_C:
                    {
                        if(currentOne->getType()==Item::CONTROL){
                            if(dynamic_cast<Control*>(currentOne)->getCount()==Control::COUNT::FIRST_c) return QString("First");
                            else return QString("Second");
                        }
                        else return QString("---");
                    }

                }
                case Qt::TextAlignmentRole:
                    return Qt::AlignCenter;
                case Qt::ForegroundRole:
                    if(colum==STATE){
                        switch(currentOne->getState()->getState()){
                            case State::completed:{
                                QBrush brush;
                                brush.setColor(Qt::green);
                                return brush;
                            }
                            case State::paused:{
                                QBrush brush;
                                brush.setColor(QColor(230, 230, 0));
                                return brush;
                            }
                            case State::stopped:{
                                QBrush brush;
                                brush.setColor(Qt::red);
                                return brush;
                            }
                            case State::inProgress:{
                                QBrush brush;
                                brush.setColor(QColor(0,153,0));
                                return brush;
                            }
                        }
                    }
                case internal_id:
                    return currentOne->getID();
                case internal_item:{
                    QVariant v;
                    v.setValue(currentOne);
                    return v;
                }
                case internal_item_next:{
                    QVariant v;
                    v.setValue(nextOne);
                    return v;
                }
                case internal_item_prev:{
                    for(int i=history->size()-1;i>=0;i--){
                        Item *item = history->at(i);
                        if(currentOne!=item&&item->getDateFrom()<=currentOne->getDateFrom()
                                &&item->equal(currentOne)){
                            QVariant v;
                            v.setValue(history->at(i));
                            return v;
                        }
                    }
                }
        }
    }
    return QVariant();
}
item_model_item::~item_model_item(){
    if(history!=NULL){
        foreach(Item *i,*history) delete i;
        delete history;
    }
}
