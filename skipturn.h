#ifndef SKIPTURN_H
#define SKIPTURN_H
#include "ability.h"
#include <memory>
#include "player.h"
#include <vector>

class SkipTurn : public Ability
{
public:
    static const int ID = 6;
    static bool use(int curPlayerID, std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players);
};

#endif
