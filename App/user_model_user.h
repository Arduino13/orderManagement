#ifndef USER_MODEL_USER_H
#define USER_MODEL_USER_H

#include <QAbstractTableModel>
#include "database_obj.h"

#define COLUM_NUM_USER 4

class user_model_user : public QAbstractTableModel
{
public:
    enum COLUMS{
        NUMBER=0,
        DATE=1,
        STATE=2,
        BATCH=3
    };

    user_model_user(QObject *parent,const User *user,const QVector<Item*>* temp);
    ~user_model_user();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void reloadData(QVector<Item*>* data);

	//Declaration of custom role
    const static int internal_id;

private:
    QVector<Item*> list;

};

#endif // USER_MODEL_USER_H
