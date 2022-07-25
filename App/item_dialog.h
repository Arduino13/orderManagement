#ifndef ITEM_DIALOG_H
#define ITEM_DIALOG_H

#include <QMainWindow>
#include <QMouseEvent>
#include "database_obj.h"
#include "item_model_item.h"
#include "hover_delegate.h"
#include "virtual_dialog.h"
#include "ui_itemtab.h"
#include "ui_state_ch.h"

#define UNKNOWN "Unknown"
#define FIRST "First"
#define SECOND "Second"

/*
 * Summary of manufactured item
 */

namespace Ui {
    class ItemTab;
    class state_ch;
}

class item_dialog : public virtual_dialog<Ui::ItemTab*>
{

Q_OBJECT

public:
	//states history can be displayed with relation to selected user or to selected
	//batch, if items are provided than it's related to batch
    item_dialog(QWidget *parent, const Item *item, const QVector<User*>* users, QVector<Item *> *items=NULL);

    ~item_dialog();

private:
    Ui::ItemTab *ui;

    void closeEvent(QCloseEvent*e);
  
    //rewrites state between from and to 
    Item* overWrite(QDateTime from, QDateTime to, Item *item_t);

	//returns next item after date or specifed row
    Item* nextItem(Item *to, int row=-1);

	//returns previous item before date or specifed row
    Item* prevItem(Item *from, int row=-1);

	//displays edit dialog or dialog to add new state 
    bool append(bool New=false);

	//reloads data
    void reloadModel();

	//determinates if states history should be loaded based on batch or id of item
    bool by_number = false; 

	//if item has thread
    bool validScrew = false; 
    bool controls_valid[2];

	//if form is editable
    bool editMode = false;

    QVector<Item*>* items; 

	//because this is only one dialog that cannont be updated when main window updates
	//it needs to story copy of opened item
    struct IDs{
        Item item_s;
        QString screw_id = NULL;
        User *user;
        const QVector<User*>* users;
    };

    IDs listID;

private slots:
    void edit(bool);
    void remove(bool);
    void customMenu(QPoint);
};

#endif // ITEM_DIALOG_H
