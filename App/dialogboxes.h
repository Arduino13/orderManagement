#ifndef DIALOGBOXES_H
#define DIALOGBOXES_H

#include <QString>
#include <QMessageBox>
#include <QIcon>

#include "log.h"

/*
 * Static class for displaying of message box 
 */

class DialogBoxes
{
public:
    static void ErrorBox(const QString msg);
    static void InfoBox(const QString msg);
    static QMessageBox* InfoBox(const QString msg, bool to_return); //to_return currently unused
    static void WarningBox(const QString msg);
    static bool ConfBox(const QString msg); //vraci true v pripade pozitivni odpovedi
private:
    DialogBoxes(); //to prevent creating instances of static class
};

#endif // DIALOGBOXES_H
