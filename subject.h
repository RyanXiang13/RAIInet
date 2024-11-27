#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "observer.h"

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
    virtual int whosTurn();
    virtual std::unique_ptr<Player> getPlayer();
    virtual ~Subject() = default;

};

#endif
