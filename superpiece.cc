#include "superpiece.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"

bool SuperPiece::use(int curPlayerID, std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players)
{
    // -------------------------------------------- SKIP FOR NOW
    // verify that
    // 1. the player has the superpiece ability
    // 2. the targetedlink is not already downloaded
    // 3. the targeted link is not the opposing player's link
    if (!players[curPlayerID]->hasAbility(SuperPiece::ID) || l->getIsDownloaded() || curPlayerID != l->getPlayerID())
    {
        return false;
    }
    // apply the superpiece

    // SKIP FOR NOW --------------------------------------------
    return true;
}
