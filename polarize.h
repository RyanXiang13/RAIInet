#ifndef POLARIZE_H
#define POLARIZE_H
#include "ability.h"
#include <vector>
#include <memory>
#include "link.h"
#include "cell.h"
#include "player.h"

class Polarize : public Ability
{
public:
    static const int ID = 4;
    static bool use(int curPlayerID, std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players);
};

#endif
