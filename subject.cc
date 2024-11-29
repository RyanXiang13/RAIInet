#include "subject.h"
#include "observer.h"
#include "player.h"
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

void Subject::displayAbilities(Player *player) {
    for (const auto&ob : observers) {
        ob->displayAbilities(*player);
    }
}

void Subject::displayWin(int winner) {
    for (const auto&ob : observers) {
        ob->displayWin(winner);
    }
}
