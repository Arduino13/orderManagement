#include "mainwindow.h"
#include <QApplication>
#include "test_db.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef TEST
    Test_db test;
    QTest::qExec(&test);
    return a.exec();
#else
    try{
        //QLibrary lib("libmysql.dll");
        //lib.load();
        //qDebug()<<lib.errorString();

        MainWindow w;
        w.show();

        return a.exec();
    }catch(exception *e){
        if(e->reason()=="auth error") DialogBoxes::ErrorBox("Incorrect password");
        else DialogBoxes::ErrorBox("Connection to database is not available");

        delete e;
        return 0;
    }
#endif
}
