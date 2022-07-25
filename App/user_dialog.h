#ifndef USER_DIALOG_H
#define USER_DIALOG_H

#include <QMainWindow>
#include <QMouseEvent>

#include "database_obj.h"
#include "hover_delegate.h"
#include "user_model_user.h"
#include "virtual_dialog.h"
#include "ui_usertab.h"

namespace Ui {
    class UserTab;
}

class user_dialog : public virtual_dialog<Ui::UserTab*>
{

Q_OBJECT

public:
    user_dialog(QWidget *parent, const User *user_temp, const QVector<Item *> *list, const QVector<User*>* users);
    ~user_dialog();
private:
    Ui::UserTab *ui;

    void closeEvent(QCloseEvent *e);

    User user;

	//if form is editable
    bool edit_mode=false;

public slots:
    void reloadData(QVector<Item*>* data);
    void editMode(bool);
    void remove(bool);
};

#endif // USER_DIALOG_H
