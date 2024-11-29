#include "skipturn.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"

bool SkipTurn::use(int curPlayerID, Game* game)
{
    // verify that player has the ability (handled by game)
    game->getPlayer(curPlayerID - 1)->setTurn(!game->getPlayer(curPlayerID - 1)->getIsTurn());
    setUsed(true);
    return true;
}
