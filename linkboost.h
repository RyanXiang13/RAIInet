#ifndef LINKBOOST_H
#define LINKBOOST_H
#include "ability.h"
#include "link.h"
#include <memory>
#include <vector>

// LinkBoost boosts a link's movement by 1 in any direction until that link is downloaded
class LinkBoost : public Ability
{
private:
    LinkBoost(int playerID = -1, bool isActive = false, bool isUsed = false);
    const int boostAmount = 1;

public:
    static std::unique_ptr<LinkBoost> create(int playerID = -1, bool isActive = false, bool isUsed = false);
    int getBoostAmount() const;
    void use(std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players) override;
};

#endif