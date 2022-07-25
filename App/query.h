#ifndef QUERY_H
#define QUERY_H

#include <QString>
#include <QObject>
#include <QVector>
#include <QDebug>
#include "exception.h"

//puts together string SQL command

class Query
{
public:
    Query();

    Query* remove(QString table);
    Query* where(QString requirment);
    Query* update(QString table);
    Query* set(QVector<QString>* columns);
    Query* insert(QString table);
    template <class T> Query* values(QVector<T> *params);

    Query* select(QVector<long> *columns);
    template<class T> Query* select(QVector<T> *columns);

    Query* from(QString table);
    QString getQuery();

private:
    QString query;
};

template<class T>
Query* Query::select(QVector<T> *columns){
    query.append("SELECT ");

    if(columns!=NULL){
        foreach(T c,*columns){
            query.append(c);
            query.append(",");
        }
        query.remove(query.lastIndexOf(","),1);
    }
    else{
        query.append("*");
    }

    return this;
}

template<class T>
Query* Query::values(QVector<T> *params){
    query.append(" VALUES(");

    int count = params->length();

    if(count==0){
        throw new exception("Parametrs cant be 0");
    }

    for(int i=0;i<count;i++){
        query.append("?,");
    }
    query.remove(query.lastIndexOf(","),1);
    query.append(");");

    return this;
}
#endif // QUERY_H
