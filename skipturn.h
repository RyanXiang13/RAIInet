#ifndef SKIPTURN_H
#define SKIPTURN_H
#include "ability.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"

class SkipTurn : public Ability
{
public:
    static const int ID = 6;
    SkipTurn() : Ability("XtraTurn", ID) {}
    bool use(int curPlayerID, Game* game) override;
};

#endif
