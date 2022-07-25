#ifndef TEST_DB_H
#define TEST_DB_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QDateTime>
#include <quuid.h>
#include <QtTest/QtTest>
#include <QTest>

#include "database_obj.h"
#include "item.h"

#define USER_ID "tfgg"
#define ITEM_ID "hggg"
#define RECORD_ID "kdjfdf"
#define SCREW_ID "dfdf"
#define CONF_ID "test_it"

class Test_db : public QObject
{

Q_OBJECT

public:
    Test_db();
private:
    database_obj db;
    State state= State(State::inProgress);
    User user = User(USER_ID,"petr_n","443-oq");
    Item item = Item(QDateTime::currentDateTime(),&state,ITEM_ID,&user,"34343","232323");
    void recordTest();

private slots:
    void test();
    void Exceptions();
};
#endif // TEST_DB_H
