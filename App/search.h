#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include <QSignalMapper>
#include <QRadioButton>
#include "database_obj.h"

#define BUTTON_NUM 6

//search prompt

namespace Ui{
    class search;
}

class search : public QDialog
{

Q_OBJECT

public:
    search(QWidget *parent, QVector<User *> *users, QVector<Item *> *items);
    ~search();

    struct search_struct{
        QString number;
        QString batch;
        State state;
        QString user_name;
        int number_of=0;
        QDate date;
        bool year_only=false;
        bool month_only=false;
    };

private:
    Ui::search *ui;
    database_obj db;
    QSignalMapper *map;

    enum BUTTON_T{
        NUMBER=0,
        BATCH=1,
        STATE=2,
        USER=3,
        NUMBER_OF=4,
        DATE=5
    };

    QRadioButton *buttonArray[BUTTON_NUM];
    BUTTON_T buttonArray_t[BUTTON_NUM]={NUMBER,BATCH,STATE,USER,NUMBER_OF,DATE};

private slots:
    void eventCatcher(int i);
    void okButton(QAbstractButton *b);

signals:
    void result(search::search_struct*);
};

Q_DECLARE_METATYPE(search::search_struct)

#endif // SEARCH_H
