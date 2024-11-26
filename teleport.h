#ifndef TELEPORT_H
#define TELEPORT_H
#include "ability.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"

class Teleport : public Ability
{
public:
    static const int ID = 8;
    bool use(int curPlayerID, std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players);
};

#endif
