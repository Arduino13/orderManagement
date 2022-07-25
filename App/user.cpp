#include "user.h"

bool User::operator ==(const User &u)const{
    return (this->id==u.getId());
}

User::User(){}

User::User(QString id, QString name, QString number)
{
    this->id=id;
    this->name=name;
    this->cardNumber=number;
}

QString User::toString(){
    return name;
}

void User::setCardNumber(QString number){
    this->cardNumber=number;
}

void User::setId(QString id){
    this->id=id;
}

void User::setName(QString name){
    this->name=name;
}

QString User::getName() const{
    return name;
}

QString User::getId() const{
    return id;
}

QString User::getCardNumber() const{
    return cardNumber;
}
