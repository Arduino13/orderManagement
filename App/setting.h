#ifndef SETTING_H
#define SETTING_H

#include <QVector>
#include <QDialog>
#include <QLabel>
#include <QPushButton>

#include "database_obj.h"

//dialog for chaning list of threads

namespace Ui{
    class setting;
}

#define COLUM_NUM_SET 2

class Setting : public QDialog
{

Q_OBJECT

public:
    Setting(QWidget *parent=0);
    ~Setting();

    QVector<QString> loadThread_list();
    bool saveThread_list(QVector<QString> save);
private:
    enum type{
        THREADS
    };

    enum COLUMS{
        TEXT=0,
        BUTTON=1
    };

    QMap<type,QString> type2str;

    database_obj db;
    Ui::setting *ui;
    QSignalMapper *map;

    void addToTable(QString str);
    void reloadTable();

private slots:
    void addEvent(bool);
    void removeEvent(int);
};

#endif // SETTING_H
