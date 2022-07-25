#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>

class Log
{
public:
    static void InfoLog(const QString msg);
    static void ErrorLog(const QString msg);
    static void WarningLog(const QString msg);
private:
    Log();
    static void write_to(const QString file_n_t, const QString msg_t, const int max_size);
};

#endif // LOG_H
