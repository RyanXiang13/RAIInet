#include <memory>
#include <vector>
#include "linkboost.h"
#include "link.h"
#include "cell.h"
#include "player.h"
#include "game.h"
#include <iostream>

bool LinkBoost::use(int curPlayerID, Game* game)
{
    // verify that
    // 1. the player has the linkboost ability
    // 2. the link is not already downloaded
    char linkID;
    std::cin >> linkID;
    Link* l = game->getLinkFromID(linkID, curPlayerID);
    
    if (!l || l->getIsDownloaded()) {
        return false;
    }
    
    // apply the linkboost on the link
    l->addMoveStrength();
    setUsed(true);
    return true;
}
