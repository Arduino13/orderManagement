#include "main_model_user.h"

const int main_model_user::internal_id=255;

main_model_user::main_model_user(QObject *parent, const QVector<User *> *list, const QVector<Item *> *list_i) :QAbstractTableModel(parent)
{
    this->list=list;
    this->list_i=list_i;
}

int main_model_user::rowCount(const QModelIndex &) const{
    if(list->size()<500) return list->size();
    else return 500;
}

int main_model_user::columnCount(const QModelIndex &) const{
    return COLUM_NUM_U;
}

QVariant main_model_user::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role==Qt::DisplayRole&&orientation==Qt::Horizontal){
        switch(section){
            case NAME:
                return QString("Name");
            case CURRENT:
                return QString("Current order");
        }
    }
    return QVariant();
}
QVariant main_model_user::data(const QModelIndex &index, int role) const{
    int row = index.row();
    COLUMS colum = static_cast<COLUMS>(index.column());
    if(list!=NULL&&list->size()>0){
        User *user = list->at(row);

        switch(role){
            case Qt::DisplayRole:
                switch(static_cast<int>(colum)){
                    case NAME:
                        return user->getName();
                    case CURRENT:
                        foreach(Item* i, *list_i){
                            if((*i->getUser())==*user&&(i->getState()->getState())!=State::completed) return i->getNumber();
                        }
                        return QString("None");
                }
            case Qt::TextAlignmentRole:
                return Qt::AlignCenter;
            case Qt::FontRole:
                if(colum==NAME){
                    QFont font;
                    font.setBold(true);
                    return font;
                }
            case internal_id:
                return user->getId();
        }
    }
    return QVariant();
}

main_model_user::~main_model_user(){
}
