#ifndef ABILITY_H
#define ABILITY_H
#include <memory>
#include <vector>
#include "game.h"
class Link;
class Cell;
class Player;

class Ability
{
protected:
    int id = 0;
    std::string name;
    bool used;
public:
    Ability(const std::string& name, int id) : id{id}, name{name}, used{false} {}
    virtual ~Ability() = default;
    virtual bool use(int curPlayerID, Game* game) = 0;

    const std::string& getName() const { return name; }
    const int& getID() const { return id; }
    bool isUsed() const { return used; }
    void setUsed(bool value) { used = value; }
};

#endif
