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
    void notifyObservers(); // uses the "push" model
    virtual ~Subject() = default;
};

#endif
