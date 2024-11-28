#include "firewall.h"
#include "cell.h"
#include "player.h"
#include "link.h"
#include <memory>
#include <vector>

char getSymbol(int playerID)
{
    if (playerID == 1)
    {
        return Firewall::symbol_1;
    }
    return Firewall::symbol_2;
}

bool Firewall::use(int curPlayerID, std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players)
{
    // verify that
    // 1. the person using it has the firewall ability
    // 2. the cell is valid
    // 3. the cell is empty and not a server port or firewall
    if (!players[curPlayerID]->hasAbility(Firewall::ID) || !c->isValid() || !c->isEmpty() || c->getIsServerPort() || c->getIsFirewall())
    {
        return false;
    }
    // successfully place the firewall
    c->setIsFirewall(curPlayerID);
    return true;
}

bool Firewall::activate(Link &l, Cell &c, const std::vector<std::unique_ptr<Player>> &players)
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
    // 2. the link must also be revealed whether or not it is a virus
    players[c.getIsFirewall()]->addKnownLink(l.getName());
    return true;
}
