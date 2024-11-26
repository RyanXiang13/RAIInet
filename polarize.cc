#include "polarize.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"

bool Polarize::use(int curPlayerID, std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players)
{
    // verify that
    // 1. the player has the polarize ability
    // 2. the link is not already downloaded
    if (!players[curPlayerID]->hasAbility(Polarize::ID) || l->getIsDownloaded())
    {
        return false;
    }
    // apply the polarize on the link
    // do not add to ability list because it is not a lasting effect, it only has one "charge"
    players[curPlayerID]->removeAbility(Polarize::ID); // remove the ability from the player (one)
    l->setIsVirus(!l->getIsVirus());                   // flip the virus status
    return true;
}
