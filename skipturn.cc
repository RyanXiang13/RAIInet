#include "skipturn.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"

bool SkipTurn::use(int curPlayerID, std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players)
{
    // verify that
    // 1. the player has the skip turn ability
    if (!players[curPlayerID]->hasAbility(SkipTurn::ID))
    {
        return false;
    }
    // apply the skip turn
    players[curPlayerID]->removeAbility(SkipTurn::ID);                   // remove the ability from the player (one)
    players[curPlayerID]->setIsTurn(!players[curPlayerID]->getIsTurn()); // flip the turn status so when it gets flipped again, it will be the same player's turn again
    // hence skipping the opposing players turn
    return true;
}
