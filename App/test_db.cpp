#include "test_db.h"
#include <QDebug>

Test_db::Test_db()
{

}

void Test_db::test(){
    for(int i=0;i<2;i++){
        QVERIFY(db.saveUser(&user)==true);
        QVERIFY(db.saveItem(&item)==true);
    }

    db.loadUser(USER_ID);
    db.loadListUser();

    db.loadItem(ITEM_ID);
    db.loadListItem();

    db.confSave(CONF_ID,"TESTING");
    db.confSave(CONF_ID,"testing2");

    Item::Screw screw = Item::Screw(SCREW_ID,"M3","M4",Item::Screw::UNKNOW);
    item.setScrew(&screw);

    QVERIFY(db.saveItem(&item)==true);
    QVERIFY((*db.loadItem(ITEM_ID)->getScrew())==static_cast<const Item::Screw>(screw));

    recordTest();

    QVERIFY(db.deleteConf(CONF_ID)==true);
    QVERIFY(db.deleteScrew(item.getScrew())==true);
    QVERIFY(db.deleteUser(&user)==true);
    QVERIFY(db.deleteItem(&item)==true);
}

void Test_db::recordTest(){
    QString id = QUuid::createUuid().toString();
    Item item = Item(this->item.getDateFrom(),&state,id,&user,"3434","2323");
    db.saveRecord(&item);

    state.setState(State::paused);
    item.setState(&state);
    db.saveRecord(&item);

    QVERIFY((*db.loadHistory(id,NULL,NULL)->first()->getUser())==user);

    db.deleteHistory();
    db.saveRecord(&item);
    db.deleteRecord(&item);
}

void Test_db::Exceptions(){
    try{
        item.setDateFrom(QDateTime());
        user.setId(NULL);
        db.saveItem(&item);
    }catch(exception *e){
        QCOMPARE(e->reason(),QString("Object is nonconsistent"));
        delete e;
    }

    try{
        db.saveUser(&user);
    }catch(exception *e){
        QCOMPARE(e->reason(),QString("Object is nonconsistent"));
        delete e;
    }

    try{
        db.loadItem("dkfjkdjf");
    }catch(exception *e){
        QCOMPARE(e->reason(),QString("item does not exist"));
        delete e;
    }

    try{
        db.loadUser("dkfdfdf");
    }catch(exception *e){
        QCOMPARE(e->reason(),QString("user does not exist"));
        delete e;
    }
}
