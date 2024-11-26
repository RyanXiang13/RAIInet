#include "teleport.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"

bool Teleport::use(int curPlayerID, std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players)
{
    // verify that
    // 1. the player has the teleport ability
    // 2. the targeted link is not already downloaded
    // 3. the targeted link is not the opposing player's link
    // 4. the targeted cell is empty
    if (!players[curPlayerID]->hasAbility(Teleport::ID) ||
        l->getIsDownloaded() ||
        curPlayerID != l->getPlayerID() ||
        !c->isEmpty())
    {
        return false;
    }
    // apply the teleport (move the link to the targeted cell)
    players[curPlayerID]->removeAbility(Teleport::ID); // remove the ability from the player (one)
    c->setLink(std::move(l));                          // transfer ownership of the link to the cell
    return true;
}
