#include "buff.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"
#include <iostream>

bool Buff::use(int curPlayerID, Game* game)
{
    char linkID;
    std::cin >> linkID;
    Link* l = game->getLinkFromID(linkID, curPlayerID);

    if (!l || l->getIsDownloaded()) {
        return false;
    }

    l->setStrength(l->getStrength() + 1);
    setUsed(true);
    return true;
}
