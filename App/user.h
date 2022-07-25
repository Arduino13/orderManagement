#ifndef USER_H
#define USER_H

#include <QString>

//represents an employee 

class User
{
public:
    User();
    User(QString id, QString name, QString number);

    QString toString();
    void setCardNumber(QString number);
    void setName(QString name);
    void setId(QString id);

    QString getName()const;
    QString getId()const;
    QString getCardNumber()const;
    bool operator ==(const User &u)const;

private:
    QString cardNumber;
    QString name;
    QString id;
};

#endif // USER_H
