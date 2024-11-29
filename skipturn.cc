#include "skipturn.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"
#include "game.h"

bool SkipTurn::use(int curPlayerID, Game* game)
{
    // verify that player has the ability (handled by game)
    game->getPlayer(curPlayerID - 1)->setExtraTurn(true);
    setUsed(true);
    return true;
}
