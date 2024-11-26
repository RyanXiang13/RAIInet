#include "scan.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"

bool Scan::use(int curPlayerID, std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players)
{
    // verify that
    // 1. the player has the scan ability
    // 2. the link is not already downloaded
    // 3. the targeted link is not the initiator player's link
    if (!players[curPlayerID]->hasAbility(Scan::ID) || l->getIsDownloaded() || curPlayerID == l->getPlayerID())
    {
        return false;
    }
    // apply the scan on the link
    // do not add to ability list because it is not a lasting effect, it only has one "charge"
    players[curPlayerID]->removeAbility(Scan::ID);    // remove the ability from the player (one)
    players[curPlayerID]->addKnownLink(l->getName()); // add to list of known links as it was just revealed
    return true;
}
