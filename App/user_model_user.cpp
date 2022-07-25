#include "user_model_user.h"

const int user_model_user::internal_id=255;

user_model_user::user_model_user(QObject *parent,const User *user,const QVector<Item*>* temp) : QAbstractTableModel(parent)
{
    foreach(Item *i,*temp){
        if(*i->getUser()==*user) list.append(i);
    }
}

int user_model_user::rowCount(const QModelIndex &) const{
    return list.size();
}

int user_model_user::columnCount(const QModelIndex &) const{
    return COLUM_NUM_USER;
}

QVariant user_model_user::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role==Qt::DisplayRole&&orientation==Qt::Horizontal){
        switch(section){
            case NUMBER:
                return QString("Drawing no.");
            case DATE:
                return QString("Date of creation");
            case STATE:
                return QString("State");
            case BATCH:
                return QString("Batch no.");
        }
    }
    return QVariant();
}

QVariant user_model_user::data(const QModelIndex &index, int role) const{
    int row = index.row();
    COLUMS colum = static_cast<COLUMS>(index.column());

    if(list.size()>0){
        Item *item = list.at(row);

        switch(role){
            case Qt::DisplayRole:
                switch(static_cast<int>(colum)){
                    case NUMBER:
                        return item->getNumber();
                    case DATE:
                        return item->getDateFrom();
                    case STATE:
                        return item->getState()->toString();
                    case BATCH:
                        return item->getBatch();
                }
            case Qt::TextAlignmentRole:
                return Qt::AlignCenter;
        case Qt::FontRole:
            if(colum==NUMBER){
                QFont font;
                font.setBold(true);
                return font;
            }
        case Qt::ForegroundRole:
            if(colum==STATE){
                switch(item->getState()->getState()){
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
            return item->getID();
        }
    }
    return QVariant();
}

user_model_user::~user_model_user(){
}
