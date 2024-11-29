#ifndef POLARIZE_H
#define POLARIZE_H
#include "ability.h"
#include <vector>
#include <memory>
#include "link.h"
#include "cell.h"
#include "player.h"

class Polarize : public Ability
{
public:
    static const int ID = 4;
    Polarize() : Ability("Polarize", ID) {}
    bool use(int curPlayerID, Game* game) override;
};

#endif
