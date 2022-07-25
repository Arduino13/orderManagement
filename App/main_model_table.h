#ifndef MAIN_MODEL_TABLE_H
#define MAIN_MODEL_TABLE_H

#include <QAbstractTableModel>
#include "database_obj.h"

#define COLUM_NUM 4

//model for main window when displaying orders

class main_model_item : public QAbstractTableModel
{

Q_OBJECT

public:
    enum COLUMS{
        DATE=1,
        NUMBER=0,
        SCREW=2,
        STATE=3
    };

	//declaration of custom role
    const static int internal_id;

    main_model_item(QObject *parent,const QVector<Item*>* list);
    ~main_model_item();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
private:
    const QVector<Item*>* list=NULL;
};

#endif // MAIN_MODEL_TABLE_H
