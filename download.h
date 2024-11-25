#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#include "ability.h"
#include <memory>
#include "link.h"
#include <vector>
#include "cell.h"
#include "player.h"

class Download : public Ability
{
public:
    static const int ID = 3;
    static std::unique_ptr<Download> create(int playerID = -1, bool isActive = false, bool isUsed = false);
    bool use(int curPlayerID, std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players);
};

#endif
