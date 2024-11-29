#ifndef BUFF_H
#define BUFF_H
#include "ability.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"

class Buff : public Ability
{
public:
    static const int ID = 7;
    Buff() : Ability("Buff", ID) {}
    bool use(int curPlayerID, Game*game) override;
};

#endif
