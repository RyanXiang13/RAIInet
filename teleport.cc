#include "teleport.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"
#include <iostream>
bool Teleport::use(int curPlayerID, Game* game)
{
    // Get link ID and destination coordinates from input
    char linkID;
    int row, col;
    std::cin >> linkID >> row >> col;
    
    Link* l = game->getLinkFromID(linkID, curPlayerID);
    Cell* c = game->getCell(row, col);
    
    // verify conditions
    if (!l || !c || l->getIsDownloaded() || !c->getIsServerPort() || !c->getCol()) {
        return false;
    }
    
    // Move the link
    game->getCell(l->getRow(), l->getCol())->setLink(nullptr);
    l->setRow(row);
    l->setCol(col);
    c->setLink(l);
    setUsed(true);
    return true;
}