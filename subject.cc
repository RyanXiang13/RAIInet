#include "subject.h"
#include "observer.h"
#include <algorithm>

void Subject::attach(std::unique_ptr<Observer> o)
{
    observers.push_back(std::move(o));
}

void Subject::detach(Observer *o)
{
    auto it = std::find_if(observers.begin(), observers.end(),
                           [o](const std::unique_ptr<Observer> &up)
                           {
                               return up.get() == o;
                           });
    if (it != observers.end())
    {
        observers.erase(it);
    }
}

void Subject::notifyObservers(Subject *game)
{
    for (const auto &ob : observers)
    {
        ob->notify(*game);
    }
}
