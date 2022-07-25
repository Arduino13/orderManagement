#ifndef ITEM_MODEL_ITEM_H
#define ITEM_MODEL_ITEM_H

#include "database_obj.h"
#include <QAbstractTableModel>

#define COLUM_NUM_ITEM 5
#define COLUM_NUM_ITEM_EXTEND 7

//model for item dialog 

class item_model_item : public QAbstractTableModel
{
public:
    enum COLUMS{
        DATE_FROM,
        DATE_TO,
        DURATION,
        STATE,
        TYPE,
        USER,
        COUNT_C
    };

    item_model_item(QObject *parent, const Item *item, bool by_number);
    ~item_model_item();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void reloadData();

	//declaration of custom roles to use with data function 
    const static int internal_id;
    const static int internal_item;
    const static int internal_item_next;
    const static int internal_item_prev;

private:
    QVector<Item*>* history=NULL;
    database_obj db;

    bool by_number=false;
    Item item;
};

#endif // ITEM_MODEL_ITEM_H
