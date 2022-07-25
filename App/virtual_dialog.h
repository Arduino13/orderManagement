#ifndef VIRTUAL_DIALOG_H
#define VIRTUAL_DIALOG_H

#include <QMainWindow>
#include <QTableView>
#include "database_obj.h"
#include "hover_delegate.h"
#include "dialogboxes.h"
#include "virtual_dialog_helper.h"

//handles initialization and hover over table, and openning of an item dialog, together 
//with it's closing, used by user dialog and item dialog

template<class T>
class virtual_dialog : public virtual_dialog_helper
{

public:
    virtual_dialog(QWidget *parent, T ui, const QVector<User *> *users);
    ~virtual_dialog();

protected:
    database_obj db;
    hover_delegate hover;
    const QVector<User*>* users;

    void closeEvent(QCloseEvent *);
    bool eventFilter(QObject *watched, QEvent *event);

    //function that handles opening of an order tab
    void choose(const QItemSelection &, const QItemSelection &);//virtual -> virtual_dialog_helper
    void onClose_sub(virtual_dialog_helper*);

    //handles right click of mouse emits menuReq signal
    void menuReq_wrapper(QPoint pos);

    void setupTable();
    T getUi();

private:
    bool running=false;
    QVector<virtual_dialog_helper*> windows;
    T ui;

};

#endif // VIRTUAL_DIALOG_H
