#ifndef SCAN_H
#define SCAN_H
#include "ability.h"
#include <memory>
#include <vector>
#include "link.h"
#include "cell.h"
#include "player.h"

class Scan : public Ability
{
public:
    static const int ID = 5;
    Scan() : Ability("Scan", ID) {}
    bool use(int curPlayerID, Game* game) override;
};

#endif
