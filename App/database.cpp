#include "database.h"
#include "dialogboxes.h"
#include <QUuid>

//#define PRODUCTION

Database::Database(QString db, QString userName, QString password)
{
    id=QUuid::createUuid().toString();
    connection = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL",id));
#ifdef PRODUCTION
    connection->setHostName("10.0.0.150");
#else
    connection->setHostName("192.168.1.234");
#endif
    connection->setDatabaseName(db);
    connection->setUserName(userName);
    connection->setPassword(password);
    bool ok = connection->open();
    if(!ok){
        throw new exception("connection_error");
    }
}

Database::~Database(){
    connection->close();
    delete connection;
    QSqlDatabase::removeDatabase(id);
}
