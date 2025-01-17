#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>

class Player;
class Observer;

class Subject
{

protected:
    std::vector<std::unique_ptr<Observer>> observers;

public:
    virtual void attach(std::unique_ptr<Observer> o);
    virtual void detach(Observer *o);
    virtual void notifyObservers(Subject *whoFrom);
    virtual void displayAbilities(Player *player);
    virtual void displayWin(int winner);
    virtual void displayWelcome();
    virtual char charAt(int row, int col) = 0;
    virtual int whosTurn() = 0;
    virtual char getState(int row, int col) const = 0;
    virtual std::unique_ptr<Player> &getPlayer(int index) = 0;
    virtual void clearObservers() = 0;
    virtual ~Subject() = default;
};

#endif
