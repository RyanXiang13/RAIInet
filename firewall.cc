#include "firewall.h"
#include "cell.h"
#include "player.h"
#include "link.h"
#include <memory>
#include <vector>
#include <iostream>

char getSymbol(int playerID)
{
    if (playerID == 1)
    {
        return Firewall::symbol_1;
    }
    return Firewall::symbol_2;
}

bool Firewall::use(int curPlayerID, Game* game)
{
    // verify that
    // 1. the person using it has the firewall ability
    // 2. the cell is valid
    // 3. the cell is empty and not a server port or firewall
    int row, col;
    std::cin >> row >> col;
    
    Cell* c = game->getCell(row, col);
    
    // verify conditions
    if (!c->isValid() || !c->isEmpty() || c->getIsServerPort() || c->getIsFirewall()) {
        return false;
    }
    
    // successfully place the firewall
    c->setIsFirewall(curPlayerID);
    setUsed(true);
    return true;
}

bool Firewall::activate(Link &l, Cell &c)
{
    // verify that
    // 1. the link and firewall are not owned by the same player
    if (l.getPlayerID() == c.getIsFirewall())
    { // no functionality according to the documentation
        return false;
    }
    // firewall is guaranteed to have an effect
    // 1. if the link is a virus, the link is downloaded by its owner
    // handled in game
    return true;
}
