#ifndef STATE_H
#define STATE_H

#include <QString>
#include <QVector>

#define STATE_SIZES 4

//represents state of an order

class State
{
public:
    State(int state);
    State();

    const static int inProgress=0;
    const static int stopped=2;
    const static int paused=1;
    const static int completed=3;
    const static int unknown=4;

	//string representation of State states
    const static QString choises[]; 

    QString toString()const;
    State* setState(int value);
    int getState() const;
    bool isValid() const; 

    static int str2state(QString str);

    bool operator ==(State state);

private:
    int state=unknown;
    const static int choises_i[];
};

#endif // STATE_H

