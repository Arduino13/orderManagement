#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>
#include <QException>

class exception : public QException
{
public:
    exception(QString reason){reason_v=reason; }
    void raise() const override { throw *this; }
    QString reason(){return reason_v; }

private:
    QString reason_v;
};

#endif // EXCEPTION_H
