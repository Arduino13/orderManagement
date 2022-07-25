#include "item.h"
#include "mainwindow.h"

//#define TEST //disables deletion of objects within item and control class

bool Item:: operator==(Item const &item) const{
    return (this->id==item.getID()&&this->getType()==item.getType());
}

bool Item::equal(const Item *item)const{
     if(!(*this==*item)&&item->getType()==TYPE_CLASS::CONTROL) return item->equal(this);
     else return true;
}

bool Item::Screw::operator ==(const Screw &item) const{
    return (this->id==item.getId()&&this->current==item.getC());
}

bool Item::sortDate(Item *i1, Item *i2){
    return (i1->getDateFrom()<i2->getDateFrom());
}

bool Item::operator =(const Item &second){
    if(second.getState()!=NULL) state=new State(*second.getState());
    if(second.getUser()!=NULL) user=new User(*second.getUser());
    if(second.getScrew()!=NULL) screw=new Screw(*second.getScrew());
    if(!second.getControl(FIRST_c)->empty()){
        foreach(Control *c,*second.getControl(FIRST_c))
        setControl(new Control(*c));
    }
    if(!second.getControl(SECOND_c)->empty()){
        foreach(Control *c,*second.getControl(SECOND_c))
        setControl(new Control(*c));
    }

    dateFrom=second.getDateFrom();
    dateTo=second.getDateTo();
    numberOf=second.getNumberOf();
    batch=second.getBatch();
    number=second.getNumber();
    id=second.getID();

    return true;
}

Item::Screw::Screw(QString id, QString left, QString right){
    this->id=id;
    left_t=left;
    right_t=right;
}

Item::Screw::Screw(QString id, QString left, QString right, screw_t current){
    this->id=id;
    left_t=left;
    right_t=right;
    this->current=current;
}

QString Item::Screw::Screw::getId() const{
    return id;
}

QString Item::Screw::getNumber() const{
    return number_s;
}

void Item::Screw::setC(screw_t current){
    this->current=current;
}

Item::Screw::screw_t Item::Screw::getC() const{
    return current;
}

QString Item::Screw::getT(screw_t type) const{
    return type==screw_t::LEFT ? left_t : right_t;
}

Item::Item(){}

Item::Item(const Item &second) : Item(){
    *this=second;
}

Item::Item(QDateTime date, State* state, QString id, User* user, QString batch, QString number) : Item()
{
    this->dateFrom=date;
    this->state=state;
    this->id=id;
    this->user=user;
    this->batch=batch;
    this->number=number;
}

void Item::setScrew(Screw *screw){
    if(this->screw!=NULL) delete this->screw;

    this->screw=screw;
    screw->number_s=number;
}

void Item::setDateFrom(QDateTime date){
    this->dateFrom=date;
}

void Item::setDateTo(QDateTime date){
    this->dateTo=date;
}

void Item::setState(State *state){
#ifndef TEST
    if(this->state!=NULL) delete this->state;
#endif
    this->state=state;
}

void Item::setID(QString id){
    this->id=id;
}

void Item::setUserID(User *ID){
#ifndef TEST
    if(this->user!=NULL) delete this->user;
#endif

    this->user=ID;
}

void Item::setBatch(QString batch){
    this->batch=batch;
}

void Item::setNumber(QString number){
    this->number=number;
}

void Item::setNumberOf(int numberOf){
    this->numberOf=numberOf;
}

void Item::setControl(Control *c){
    switch(static_cast<int>(c->getCount())){
        case Control::FIRST_c:
        {
            controls[static_cast<int>(FIRST_c)].append(c);
            break;
        }
        case Control::SECOND_c:
        {
            controls[static_cast<int>(SECOND_c)].append(c);
            break;
        }
    }
}

QDateTime Item::getDateFrom() const{
    return dateFrom;
}

QDateTime Item::getDateTo() const{
    return dateTo;
}

QString Item::getDateFromS() const{
    return dateFrom.toString();
}

QString Item::getDateToS() const{
    if(!dateTo.isNull()) return dateTo.toString();
    return QString("");
}

State *Item::getState() const{
    return state;
}

QString Item::getID() const{
    return id;
}

User *Item::getUser() const{
    return user;
}

QString Item::getBatch() const{
    return batch;
}

QString Item::getNumber() const{
    return number;
}

const Item::Screw *Item::getScrew() const{
    return screw;
}

int Item::getNumberOf() const{
    return numberOf;
}

const QVector<Control*>* Item::getControl(CONTROL_T type) const{
    return &controls[static_cast<int>(type)];
}

Item::TYPE_CLASS Item::getType()const{
    return ITEM;
}

Item::~Item(){
#ifndef TEST
    foreach(Control *c,*getControl(FIRST_c)) delete c;
    foreach(Control *c,*getControl(SECOND_c)) delete c;
    if(user!=NULL) delete user;
    if(state!=NULL) delete state;
    if(screw!=NULL) delete screw;
#endif
}

Control::Control(QString id,QString batch, QString number, User *u, COUNT count, QDateTime from) : Item(from,new State(State::inProgress),id,u,batch,number){
    this->count=count;
}

Control::Control(Control &second) : Item(second.getDateFrom(),new State(*second.getState()),second.getID(),new User(*second.getUser()),
                                         second.getBatch(),second.getNumber()){
    count=second.getCount();
    reason=second.getReason();
}

void Control::setReason(QString reason){
    if(reason!="") this->reason=reason;
}

void Control::setCount(COUNT count){
    this->count=count;
}

QString Control::getReason() const{
    return reason;
}

Control::COUNT Control::getCount()const{
    return count;
}

Control::TYPE_CLASS Control::getType()const{
    return CONTROL;
}

bool Control:: operator==(Control const &control)const{
    return (this->getBatch()==control.getBatch()&&this->getNumber()==control.getNumber()&&this->getCount()==control.getCount());
}

bool Control::equal(const Item *item) const{
    const Control *con = dynamic_cast<const Control*>(item);
    if(con!=NULL) return *this==*con;
    else{
        return (*this->getUser()==*item->getUser()&&this->getBatch()==item->getBatch()&&this->getNumber()==item->getNumber());
    }
}

