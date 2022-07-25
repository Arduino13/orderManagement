#ifndef MAIN_MODEL_USER_H
#define MAIN_MODEL_USER_H

#include <QVariant>
#include <QAbstractItemModel>
#include "database_obj.h"

#define COLUM_NUM_U 2

//model for main window when displaying users

class main_model_user : public QAbstractTableModel
{
public:
    enum COLUMS{
        NAME=0,
        CURRENT=1,
        CARD=2
    };

	//declaration of custom role
    const static int internal_id;

    main_model_user(QObject *parent, const QVector<User*>* list, const QVector<Item*>* list_i);
    ~main_model_user();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
private:
    const QVector<User*>* list=NULL;
    const QVector<Item*>* list_i=NULL;
};

#endif // MAIN_MODEL_USER_H
