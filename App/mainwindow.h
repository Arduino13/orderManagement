#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "query.h"
#include "dialogboxes.h"
#include "main_model_table.h"
#include "main_model_user.h"
#include "hover_delegate.h"
#include "user_dialog.h"
#include "item_dialog.h"
#include "setting.h"
#include "search.h"
#include "password_dialog.h"

//#define TEST tests database see test_db.h

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void resizeEvent(QResizeEvent *e);
    bool eventFilter(QObject *watched, QEvent *event);
    ~MainWindow();

private:
	//helper strucutures for bar menus
    enum CHECKED{
        ITEMS,
        USERS
    };
    enum ITEMS_SORT{
        BY_NUMBER,
        BY_ID
    };

    void reloadData(search::search_struct* =NULL);
    void closeEvent(QCloseEvent *e); 

    Ui::MainWindow *ui;
    database_obj db;

	//to prevent running choose function multiple times
    bool running=false;
	
	//part of error function 
    bool error_c=false;

	//previously selected options in menu bar
    CHECKED prev_ch = ITEMS;
    ITEMS_SORT prev_ch_items=BY_ID;

    hover_delegate *hover;

	//currently opend windows by mainwindow
    QVector<virtual_dialog_helper*> windows;

	//main data of application 
    QVector<User*>* users;
    QVector<Item*>* items;

	//temporaly database for main window in case of searching
    QVector<Item*>* items_search;

    bool will_remove = false;
public slots:
	//to throw exception in main thread, used by passwd_dialog
    void error(exception *e);

private slots:
	//when menu bar items selection changes
    void choose(const QItemSelection &,const QItemSelection &);

    bool reloadTable(bool not_first, search::search_struct *item=NULL);
    bool reloadTable(search::search_struct *item=NULL);

	//displays search prompt
    void items_sort(bool); 

	//removes window from windows list;
    void dialog_on_close(virtual_dialog_helper *);

    void run_setting(bool);
    void run_search();
    void Delete_all(bool);
    void change_password(bool);

signals:
	//notifies opened windows about data change 
    void dataChanged(QVector<Item*>* data);
};

#endif // MAINWINDOW_H
