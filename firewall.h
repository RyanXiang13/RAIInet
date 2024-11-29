#ifndef FIREWALL_H
#define FIREWALL_H
#include "ability.h"
#include "cell.h"
#include "player.h"
#include "link.h"
#include <memory>
#include <vector>

class Firewall : public Ability
{
public:
    static const int ID = 2;
    static const char symbol_1 = 'm';
    static const char symbol_2 = 'w';
    static char getSymbol(int playerID);
    Firewall() : Ability("Firewall", ID) {}
    bool use(int curPlayerID, Game* game) override;
    //static bool activate(Link &l, Cell &c, const std::vector<std::unique_ptr<Player>> &players);
};

#endif
