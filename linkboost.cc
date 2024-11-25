#include <memory>
#include <vector>
#include "linkboost.h"
#include "link.h"
#include "cell.h"
#include "player.h"

bool LinkBoost::use(int curPlayerID, std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players)
{
    // verify that
    // 1. the player has the linkboost ability
    // 2. the link is not already downloaded
    if (!l->hasAbility(LinkBoost::ID) || !l->getIsDownloaded())
    {
        return false;
    }
    // boost the link
    l->addMoveStrength();                               // adds 1 to the move strength of the link
    l->addAbility(LinkBoost::ID);                       // add to link's list of abilities
    players[curPlayerID]->removeAbility(LinkBoost::ID); // remove from player's list of abilities
    return true;
}
