#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QVector>
#include <QtSql>

#include "exception"
#include "query.h"
#include "log.h"
#include <QDebug>

/*
 * Handles basic database functions insert, update etc.
 * Everythink is done using templates, but type is in reality restricted to QVariant
 */

class Database
{
public:
    Database(QString db,QString userName, QString password);
    ~Database();

    template<class T> bool remove(QString table, QString requriment, QVector<T>* params);
    template<class T> bool insert(QString table,QVector<T>* params);
    template<class T> QSqlQuery* select(QString table, QVector<QString>* columns, QVector<T>* params);

	//variant with WHERE expression
    template<class T> QSqlQuery* select(QString table, QVector<QString>* columns, QString requirement, QVector<T>* params); 
    template<class T> bool update(QString table,QVector<QString>* columns, QString requirement, QVector<T>* params);

private:
	//bind values to query and executes it
    template<class T> bool query_f(QVector<T>* params, QString query);

	//variant for SELECT 
    template<class T> QSqlQuery* query_f(QString query, QVector<T>* params);

    QSqlDatabase *connection;
    QString id;
    Query* query;
};

#endif // DATABASE_H

template<class T>
QSqlQuery* Database::query_f(QString query, QVector<T>* params){
    QSqlQuery *ps = new QSqlQuery(*connection);
    ps->prepare(query);

    if(params!=NULL){
        foreach(T temp,*params){
            ps->addBindValue(temp);
        }
    }
    ps->exec();
    Log::InfoLog(query);
    return ps;
}

template<class T>
bool Database::query_f(QVector<T>* params, QString query){
    QSqlQuery ps(*connection);
    ps.prepare(query);

    if(params!=NULL){
        foreach(T temp,*params){
            ps.addBindValue(temp);
        }
    }

    Log::InfoLog(query);
    bool to_return=ps.exec();
    return to_return;
}

template<class T>
bool Database::remove(QString table, QString requriment, QVector<T>* params){
    query = new Query();
    if(requriment!=""){
        query->remove(table)->where(requriment);
    }
    else{
        query->remove(table);
    }

    bool to_return = query_f(params,query->getQuery());
    delete query;
    return to_return;
}

template<class T>
bool Database::insert(QString table, QVector<T>* params){
    query = new Query();
    query->insert(table)->values(params);

    bool to_return=query_f(params,query->getQuery());
    delete query;
    return to_return;
}

template<class T>
QSqlQuery* Database::select(QString table, QVector<QString>* columns, QString requirement, QVector<T>* params){
    query = new Query();

    if(requirement!=""){
        query->select(columns)->from(table)->where(requirement);
    }
    else{
        query->select(columns)->from(table);
    }

    QSqlQuery* to_return=query_f(query->getQuery(),params);
    delete query;
    return to_return;
}

template<class T>
QSqlQuery* Database::select(QString table, QVector<QString>* columns, QVector<T>* params){
    return select(table,columns,"",params);
}

template<class T>
bool Database::update(QString table,QVector<QString>* columns, QString requirement, QVector<T>* params){
    query = new Query();

    query->update(table)->set(columns)->where(requirement);

    bool to_return = query_f(params,query->getQuery());
    delete query;
    return to_return;
}
