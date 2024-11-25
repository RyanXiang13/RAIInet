#ifndef LINKBOOST_H
#define LINKBOOST_H
#include "ability.h"
#include "link.h"
#include <memory>
#include <vector>

// LinkBoost boosts a link's movement by 1 in any direction until that link is downloaded
class LinkBoost : public Ability
{
public:
    static const int ID = 1;
    const int boostAmount = 1;
    bool use(int curPlayerID, std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players);
};

#endif
