#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "observer.h"

class Player;
class Observer;

class Subject {
    
protected:
    void notifyObservers();
    std::vector<std::unique_ptr<Observer>> observers;

public:
    virtual void attach(std::unique_ptr<Observer> o);
    virtual void detach(Observer* o);
    virtual void notifyObservers(Subject* whoFrom);
    virtual char charAt(int row, int col) = 0;
    virtual int whosTurn() = 0;
    virtual char getState(int row, int col) const = 0;
    virtual std::unique_ptr<Player>& getPlayer(int index) = 0;
    virtual ~Subject() = default;    
};

#endif
