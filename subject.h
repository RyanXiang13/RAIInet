#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "observer.h"

class Player;
class Observer;

class Subject
{
    std::vector<std::unique_ptr<Observer>> observers;
    
protected:
    void notifyObservers();

public:
    void attach(std::unique_ptr<Observer> o);
    void detach(std::unique_ptr<Observer> o);
    void notifyObservers(Subject* game); // uses the "push" model
    virtual char charAt(int row, int col) = 0;
    virtual int whosTurn() = 0;
    virtual char getState(int row, int col) const = 0;
    virtual std::unique_ptr<Player>& getPlayer(int index) = 0;
    virtual ~Subject() = default;    

};

#endif
