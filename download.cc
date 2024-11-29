#include "download.h"
#include <memory>
#include "link.h"
#include <vector>
#include <iostream>
#include "cell.h"
#include "player.h"
#include "game.h"
bool Download::use(int curPlayerID, Game* game)
{
    // verify that
    // 1. the person using it is targeting an opponents link
    // 2. the link is not already downloaded
    // 3. the initiator player has the download ability
    char linkID;
    std::cin >> linkID;
    Link* l = game->getLinkFromID(linkID, game->notTurn());

    if (curPlayerID == l->getPlayerID() || l->getIsDownloaded())
    {
        return false;
    }
    // successfully download the link
    game->getPlayer(curPlayerID)->download(l);
    setUsed(true);
    return true;
}
