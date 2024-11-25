#include "download.h"
#include <memory>
#include "link.h"
#include <vector>
#include "cell.h"
#include "player.h"

bool Download::use(int curPlayerID, std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players)
{
    // verify that
    // 1. the person using it is targeting an opponents link
    // 2. the link is not already downloaded
    // 3. the initiator player has the download ability
    if (curPlayerID != l->getPlayerID() || l->getIsDownloaded() || !players[curPlayerID]->hasAbility(Download::ID))
    {
        return false;
    }
    // successfully download the link
    l->setIsDownloaded(true);                              // set the link to inactive
    players[curPlayerID]->removeAbility(Download::ID);     // remove from initiator player's list of abilities
    players[curPlayerID]->addDownloadedLink(std::move(l)); // add to initiator player's list of downloaded links
    players[curPlayerID]->addKnownLink(l->getName());      // add to initiator player's list of known links
    return true;
}
