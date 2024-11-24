#ifndef ABILITY_H
#define ABILITY_H
#include <memory>
#include "link.h"
#include "cell.h"
#include "player.h"

class Ability
{
private:
    int playerID;  // -1 if not assigned to a player, 1 if assigned to player 1, 2 if assigned to player 2
    bool isActive; // true if the ability is currently active, false otherwise
    bool isUsed;   // true if the ability has been used this turn, false otherwise

public:
    virtual void use(std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players) = 0;
    virtual ~Ability() = default;
};

#endif