#include "log.h"

Log::Log()
{

}

void Log::write_to(const QString file_n_t, const QString msg_t, const int max_size){
    QDateTime time =  QDateTime::currentDateTime();

    QString msg(QString::fromStdString(msg_t.toStdString()));
    QString file_n(QString::fromStdString(file_n_t.toStdString()));

    QDir dir(QDir::homePath()+"/"+"AppData"+"/"+"Local"+"/"+"Sprava_zakazek");
    if(!dir.exists()) dir.mkdir(QDir::homePath()+"/"+"AppData"+"/"+"Local"+"/"+"Sprava_zakazek");

    file_n=QDir::homePath()+"/"+"AppData"+"/"+"Local"+"/"+"Sprava_zakazek"+"/"+file_n;
    QFile outFile(file_n);

    msg=time.toString("dd.MM.yyyy hh:mm:ss ")+": "+msg;

    if(outFile.size()>(max_size*1000000)){
        outFile.close();
        QDir dir;
        dir.remove(file_n);;
    }

    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << msg << endl;
    outFile.close();
}

void Log::InfoLog(const QString msg){
    qDebug()<<msg;
    write_to("info.log",msg,100);
}
void Log::ErrorLog(const QString msg){
    qCritical()<<msg;
    write_to("error.log",msg,10);
}
void Log::WarningLog(const QString msg){
    qWarning()<<msg;
    write_to("warning.log",msg,10);
}
