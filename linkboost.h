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
    LinkBoost() : Ability("LinkBoost", ID) {}
    bool use(int curPlayerID, Game* game) override;
};

#endif
