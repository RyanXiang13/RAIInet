#include "download.h"
#include <memory>
#include "link.h"
#include <vector>
#include <iostream>
#include "cell.h"
#include "player.h"
#include "game.h"
#include <iostream>
bool Download::use(int curPlayerID, Game* game)
{
    char linkID;
    std::cin >> linkID;
    Link* l = game->getLinkFromID(linkID, game->notTurn());
    std::cout << game->notTurn() << std::endl;
    // Add nullptr check
    if (!l || curPlayerID == l->getPlayerID() || l->getIsDownloaded())
    {
        return false;
    }
    
    // successfully download the link
    game->getPlayer(curPlayerID - 1)->download(l);
    game->getCell(l->getRow(), l->getCol())->setLink(nullptr);
    std::cout << curPlayerID << std::endl;
    setUsed(true);
    return true;
}
