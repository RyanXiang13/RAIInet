#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "player.h"

class Subject;
class Observer
{
public:
    virtual void notify(Subject &subject) = 0;
    virtual void displayAbilities(Player &player) = 0;
    virtual void displayWin(int winner) = 0;
    virtual void displayWelcome() = 0;
    virtual ~Observer() = default;
};

#endif
