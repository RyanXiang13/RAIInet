#ifndef TELEPORT_H
#define TELEPORT_H
#include "ability.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"

class Teleport : public Ability
{
public:
    static const int ID = 8;
    Teleport() : Ability("Teleport", ID) {}
    bool use(int curPlayerID, Game* game) override;
};

#endif
