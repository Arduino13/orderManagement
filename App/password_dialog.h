#ifndef PASSWORD_DIALOG_H
#define PASSWORD_DIALOG_H

#include "database_obj.h"
#include <QAbstractButton>
#include <QDialog>

namespace Ui{
    class password_d;
}

class password_dialog : public QDialog
{

Q_OBJECT

public:
    database_obj db;
    password_dialog(QWidget *parent=0, bool add=false);
    ~password_dialog();

private:
    Ui::password_d *ui;
    bool add=false;

private slots:
    void buttonClick(QAbstractButton *b);
    void passHide(bool);
signals:
    int result(bool correct); // in case of login to application
    int result(QString New); // in case of the password update
    int error(exception *e);
};

#endif // PASSWORD_DIALOG_H
