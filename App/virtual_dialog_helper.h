#ifndef VIRTUAL_DIALOG_HELPER_H
#define VIRTUAL_DIALOG_HELPER_H

#include <QMainWindow>
#include <QTableView>

/*
 * Qt doesn't support slots and signals inside templates (2019), that's why signals need
 * to be declared here and slots as virtual function and this class is then inherited
 * by template class
 */

class virtual_dialog_helper : public QMainWindow 
{

Q_OBJECT

public:
    virtual_dialog_helper(QWidget *parent);
    ~virtual_dialog_helper();

protected:
    void onClose_support();

protected slots:
    virtual void choose(const QItemSelection &, const QItemSelection &) = 0;
    virtual void onClose_sub(virtual_dialog_helper*) = 0;
    virtual void menuReq_wrapper(QPoint pos) = 0;

signals:
    void onClose(virtual_dialog_helper*);
    void menuReq(QPoint pos);
    void reloadMain(bool);
};

#endif // VIRTUAL_DIALOG_HELPER_H
