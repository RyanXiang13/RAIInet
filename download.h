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
    Download() : Ability("Download", ID) {}
    bool use(int curPlayerID, Game* game);
};

#endif
