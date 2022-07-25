#include "query.h"

Query::Query(){}

Query* Query::remove(QString table){
    query.append("DELETE FROM ");
    query.append(table);
    return this;
}

Query* Query::where(QString requirment){
    query.append(" WHERE ");
    query.append(requirment);
    return this;
}

Query* Query::update(QString table){
    query.append("UPDATE ");
    query.append(table);
    query.append(" SET ");
    return this;
}

Query* Query::set(QVector<QString> *columns){
    int count = columns->length();
    if(count == 0){
        throw new exception("Parametrs cant be 0");
    }

    foreach(QString s,*columns){
        query.append(s);
        query.append(" = ");
        query.append("?");
        query.append(",");
    }
    query.remove(query.lastIndexOf(","),1);
    return this;
}

Query* Query::insert(QString table){
    query.append("INSERT INTO ");
    query.append(table);
    return this;
}


Query* Query::select(QVector<long> *columns){
    QVector<QString> pole;
    foreach(int i, *columns){
        pole.append(QString::number(i));
    }
    return select(&pole);
}

Query* Query::from(QString table){
    query.append(" FROM ");
    query.append(table);
    return this;
}

QString Query::getQuery(){
    return query;
}

