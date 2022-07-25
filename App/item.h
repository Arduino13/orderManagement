#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QDateTime>
#include <QVariant>

#include "user.h"
#include "state.h"

/*
 * Class represents manufactured item, with thread which is represented by
 * Screw class. Control represents two step process of controlling if item
 * was manufactured correctly.
 */

class Control;

class Item
{
public:
    class Screw{
        public:
            enum screw_t{
                    LEFT,
                    RIGHT,
                    UNKNOW
            };

            Screw(QString id, QString left, QString right, screw_t current);
            Screw(QString id, QString left, QString right);
            QString getId()const;
            QString getNumber()const;
            void setC(screw_t current);
            screw_t getC()const;
            QString getT(screw_t type)const;

            bool operator ==(const Screw &screw)const;
        private:
            QString id;
            QString left_t;
            QString right_t;
            QString number_s;
            screw_t current = screw_t::UNKNOW;

        friend class Item;
    };
    enum CONTROL_T{
        FIRST_c=0,
        SECOND_c=1
    };

    enum TYPE_CLASS{
        ITEM,
        CONTROL
    };

    Item();
    Item(QDateTime date, State *state, QString id, User *user, QString batch, QString number);
    Item(const Item& second);
    Item(const Item* second);
    virtual ~Item();

    void setScrew(Screw* screw);
    void setDateFrom(QDateTime date);
    void setDateTo(QDateTime);
    void setState(State* state);
    void setID(QString id);
    void setUserID(User* ID);
    void setBatch(QString batch);
    void setNumber(QString number);
    void setNumberOf(int numberOf);
    void setControl(Control *c);

    static bool sortDate(Item *i1, Item *i2);
    //used by std::sort 

    virtual TYPE_CLASS getType() const;

    QDateTime getDateFrom()const;
    QDateTime getDateTo()const;
    QString getDateFromS()const;
    QString getDateToS()const;
    State* getState()const;
    QString getID()const;
    User* getUser()const;
    QString getBatch()const;
    QString getNumber()const;
    const Screw* getScrew()const;

    int getNumberOf()const;
    const QVector<Control *> *getControl(CONTROL_T type)const;

    bool operator ==(Item const &item)const;
    bool operator =(const Item &item);

	//to compare control object and item object 
    virtual bool equal(const Item *item)const;

private:
    QDateTime dateFrom;
    QDateTime dateTo;
    State* state=NULL;
    QString id;
    User* user=NULL;
    QString batch;
    QString number;
    Screw* screw=NULL;
    int numberOf=0;
    QVector<Control*> controls[2] = {QVector<Control*>(),QVector<Control*>()};
};

class Control : public Item{
    public:
        enum COUNT{
            FIRST_c=1,
            SECOND_c=2,
            UNKNOW_c=3
        };

        Control();
        Control(Control &second);
        Control(QString id, QString batch, QString number, User *u, COUNT count, QDateTime from);

        COUNT getCount()const;
        QString getReason()const;

        void setCount(COUNT count);
        void setReason(QString reason);

        TYPE_CLASS getType()const;

        bool operator==(Control const &control)const;
        bool equal(const Item *item)const;
    private:
        COUNT count;
        QString reason;
};

//declaration for QT to be part of QVariant 
Q_DECLARE_METATYPE(Item*)

#endif // ITEM_H
