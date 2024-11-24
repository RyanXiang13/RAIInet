#ifndef SKIPTURN_H
#define SKIPTURN_H
#include "ability.h"
#include <memory>
#include "player.h"
#include <vector>

class SkipTurn : public Ability
{
private:
    SkipTurn(int playerID = -1, bool isActive = false, bool isUsed = false);

public:
    static std::unique_ptr<SkipTurn> create(int playerID = -1, bool isActive = false, bool isUsed = false);
    void use(std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players) override;
};

#endif