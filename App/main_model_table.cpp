#include "main_model_table.h"
#include <QLinearGradient>

const int main_model_item::internal_id=255;

main_model_item::main_model_item(QObject *parent, const QVector<Item *> *list) :QAbstractTableModel(parent)
{
    this->list=list;
}

int main_model_item::rowCount(const QModelIndex &) const{
    if(list->size()<500) return list->size();
    else return 500;
}

int main_model_item::columnCount(const QModelIndex &) const{
    return COLUM_NUM;
}


QVariant main_model_item::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role==Qt::DisplayRole&&orientation==Qt::Horizontal){
        switch(section){
            case DATE:
                return QString("Date of creation");
            case NUMBER:
                return QString("Drawing no.");
            case SCREW:
                return QString("Rolling side");
            case STATE:
                return QString("State");
        }
    }
    if(role==Qt::ForegroundRole&&orientation==Qt::Horizontal){
        return QBrush(Qt::white);
    }
    return QVariant();
}

QVariant main_model_item::data(const QModelIndex &index, int role) const{
    int row = index.row();
    COLUMS col = static_cast<COLUMS>(index.column());

    if(list!=NULL&&list->size()>0){

        Item *item = list->at(row);

        switch(role){
            case Qt::DisplayRole:
                switch(col){
                    case DATE:
                        return item->getDateFrom();
                    case NUMBER:
                        return item->getNumber();
                    case SCREW:
                        if(item->getScrew()!=NULL) return item->getScrew()->getC()==Item::Screw::LEFT ? "First" : "Second";
                    case STATE:
                        return item->getState()->toString();
                    default:
                        return QString("");
                }
            case Qt::TextAlignmentRole:
                return Qt::AlignCenter;
            case Qt::FontRole:
                if(col==NUMBER){
                    QFont font;
                    font.setBold(true);
                    return font;
                }
            case Qt::ForegroundRole:
                if(col==STATE){
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

main_model_item::~main_model_item(){
}
