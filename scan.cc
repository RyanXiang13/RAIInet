#include "scan.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"
#include <iostream>
#include "game.h"

bool Scan::use(int curPlayerID, Game* game)
{
    char linkID;
    std::cin >> linkID;
    Link* l = game->getLinkFromID(linkID, game->notTurn());
    
    if (!l || l->getIsDownloaded() || curPlayerID == l->getPlayerID()) {
        return false;
    }
    
    l->setIsFound(true);
    setUsed(true);
    return true;
}
