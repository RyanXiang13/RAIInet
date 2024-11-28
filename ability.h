#ifndef ABILITY_H
#define ABILITY_H
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"
class Link;
class Cell;
class Player;

class Ability // Pure static utility class, no instantiation
{
protected:
    static const int ID = 0;
    static bool use(int curPlayerID, std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players);
};

#endif
