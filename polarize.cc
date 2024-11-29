#include "polarize.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"
#include <iostream>

bool Polarize::use(int curPlayerID, Game* game)
{
    // verify that
    // 1. the player has the polarize ability
    // 2. the link is not already downloaded
    char linkID;
    std::cin >> linkID;
    Link* l = game->getLinkFromID(linkID, game->notTurn());
    
    if (!l) {
        l = game->getLinkFromID(linkID, curPlayerID);
    }
    if (!l || l->getIsDownloaded()) {
        return false;
    }
    
    l->setIsVirus(!l->getIsVirus());
    setUsed(true);
    return true;
}
