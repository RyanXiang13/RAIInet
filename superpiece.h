#ifndef SUPERPIECE_H
#define SUPERPIECE_H
#include "ability.h"
#include <memory>
#include "link.h"
#include <vector>

class SuperPiece : public Ability
{
private:
    static const int ID = 7;
    SuperPiece(int playerID = -1, bool isActive = false, bool isUsed = false);

public:
    static std::unique_ptr<SuperPiece> create(int playerID = -1, bool isActive = false, bool isUsed = false);
    bool use(int curPlayerID, std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players);
};

#endif
