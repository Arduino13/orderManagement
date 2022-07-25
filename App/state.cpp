#include "state.h"

const QString State::choises[]={"done","in progress","stopped","paused"};
const int State::choises_i[]={completed,inProgress,stopped,paused};


bool State::operator ==(State state){
    return (this->getState()==state.getState());
}

State::State(){}

State::State(int state)
{
    this->state=state;
}

QString State::toString() const{
    switch(state){
    case inProgress:
        return "in progress";
    case stopped:
        return "stopped";
    case paused:
        return "paused";
    case completed:
        return "done";
    }
    return "unknown";
}

State *State::setState(int value){
    state=value;
    return this;
}

int State::getState() const{
    return state;
}

bool State::isValid() const{
    return state>=0&&state<STATE_SIZES;
}

int State::str2state(QString str){
    QVector<QString> temp;
    temp.reserve(STATE_SIZES);

    std::copy(choises,choises+STATE_SIZES,std::back_inserter(temp));

    if(temp.indexOf(str)!=-1){
        return choises_i[temp.indexOf(str)];
    }
    else return unknown;
}
