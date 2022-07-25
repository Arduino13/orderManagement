#ifndef DATABASE_OBJ_H
#define DATABASE_OBJ_H

#include "item.h"
#include <QVector>
#include <QString>
#include <QMap>
#include <functional>

#include "database.h"
#include "exception.h"

/*
 * Handles saving, loading and deleting of application objects
 * Because every call is openning new connection to database, which can slow
 * down the application an QSqlRecord can be passed, which is loaded item from database
 * but unparsed. 
 */

class database_obj
{
public:
    database_obj();
    bool saveItem(const Item *to_save);
    bool saveUser(const User *to_save);
    bool threadSave(const Item::Screw* item);
    bool saveRecord(const Item *item);
    bool confSave(const QString id, const QString conf);
    bool saveControl(const Control *control);

	//saves record to history table
    bool saveControl_h(const Control *control);

    User* loadUser(const QString id, QSqlRecord rec=QSqlRecord());

	//rec_u is sql record for user and rec_s is for screw
    Item* loadItem(const QString id, QSqlRecord rec=QSqlRecord(), QSqlRecord rec_u=QSqlRecord(), QSqlRecord rec_s=QSqlRecord());

    //limit and index are currently unused
    QVector<Item*>* loadListItem(int limit=0,int index=0);
    QVector<User*>* loadListUser();
    QVector<Item*>* loadHistory(const QString id, const QString number, const QString batch, const QVector<Item *> *list =NULL);
    QVector<Control*>* loadHistory_c(const QString id, const QString number, const QString batch, const QVector<Control*>* list=NULL);
    QString confLoad(const QString id);

	//rec_u is sql record for user
    Control* loadControl(const QString id, QSqlRecord rec=QSqlRecord(), QSqlRecord rec_u=QSqlRecord());
    QVector<Control*>* loadListControl(int limit=0,int index =0);

    void loadControlsTo(QVector<Item*>* list);

    bool deleteUser(const User* user);
    bool deleteItem(const Item* item);
    bool deleteHistory();
    bool deleteRecord(const Item *item);
    bool deleteConf(const QString id);
    bool deleteScrew(const Item::Screw* screw);
    bool deleteControl(const Control* control);
	
	//deletes history record 
    bool deleteRecord_c(const Control* control);
private:
	//see line no. 409
    typedef std::function<QVector<Item*>* (const QString,QVector<User*>*,Item *item,int,int)> getter_f;

    QString name_db = "DB NAME";
    QString name = "DB USER";
    QString pass = "DB PASSWORD";

    enum type{
        USER=1,
        RECORD=2,
        HISTORY_R=3,
        CONF=4,
        SCREW=5,
        CONTROL=6,
        HISTORY_C=7
    };

    QMap<type,QString> type2str; //maps type to table in database
    QMap<Control::COUNT,QString> num2str_c; //maps control type to string

    Database *open();
    bool TestIt(QSqlQuery* rs); //test if rs is empty
	
	//because Screw is inner class it never should be loaded alone without item
    Item::Screw* threadLoad(const QString id, QSqlRecord rec=QSqlRecord());
    template<class T> bool exist(type typ, T id);

    long timeOffset = 0; //to correct for time zone, databases uses UTC

    bool saveRecord(const Item *item, const type what);

	/*
	 * first layer of loading history consist of public loadHistory and loadHistory_c functions
	 * they call next layer with getter ,which is a lambda function, for loading history
	 * for item or for control object, this layer filters history based on given
	 * batch or id.
	 * Third layer parses data from database, but casting is done in first layer
	 */

	//fourth layer the actual reading from database
    QVector<Item*>* loadHistory(const QString id, QVector<User *> *u_temp, int limit, int index, const type what);

	//third layer
    QVector<Item*>* loadHistory(const QString id, QVector<User *> *u_temp, int limit, int index);
    QVector<Item *> *loadHistory_c(const QString id, QVector<User*>* u_temp,int limit, int index);

	//second layer
    QVector<Item*>* loadHistory(const QString id, const QString number, const QString batch, int limit, int index, getter_f function);
};

template<class T>
bool database_obj::exist(type typ, T id){
    Database *db = open();
    QVector<QString> colum({"*"});
    QVector<T> id_vect({id});

    bool to_return=false;

    switch(static_cast<int>(typ)){
        case USER:
        {
            QSqlQuery* rs = db->select(type2str[type::USER],&colum,"id = ?",&id_vect);
            to_return = TestIt(rs);
            delete rs;
            break;
        }
        case RECORD:
        {
            QSqlQuery* rs2 = db->select(type2str[type::RECORD],&colum, "id = ?", &id_vect);
            to_return = TestIt(rs2);
            delete rs2;
            break;
        }
       case HISTORY_R:
        {
             QSqlQuery* rs3 = db->select(type2str[type::HISTORY_R],&colum, "date = ?", &id_vect);
             to_return = TestIt(rs3);
             delete rs3;
             break;
        }
       case CONF:
        {
            QSqlQuery* rs4 = db->select(type2str[type::CONF],&colum, "id = ?", &id_vect);
            to_return = TestIt(rs4);
            delete rs4;
            break;
        }
       case SCREW:
        {
            QSqlQuery* rs5 = db->select(type2str[type::SCREW],&colum, "id = ?", &id_vect);
            to_return = TestIt(rs5);
            delete rs5;
            break;
        }
        case CONTROL:
        {
            QSqlQuery* rs6 = db->select(type2str[type::CONTROL],&colum,"id = ?", &id_vect);
            to_return = TestIt(rs6);
            delete rs6;
            break;
        }
        case HISTORY_C:
        {
            QSqlQuery * rs7 = db->select(type2str[type::HISTORY_C],&colum,"date = ?", &id_vect);
            to_return = TestIt(rs7);
            delete rs7;
            break;
        }
    }
    return to_return;
}
#endif // DATABASE_OBJ_H
