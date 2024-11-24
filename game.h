#ifndef GAME_H
#define GAME_H
#include "subject.h"
#include "cell.h"
#include <vector>
#include <memory>
#include "player.h"

class Game : public Subject
{
private:
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::vector<std::unique_ptr<Cell>>> board;
    std::vector<Link> links;
    const int width = 8;
    const int height = 8;

public:
    Game(std::unique_ptr<Player> p1, std::unique_ptr<Player> p2);
    void initBoard();
    void initLinks();
    void setUpdates(bool downloadedLinks, bool abilityCounter, bool knownLinks, bool cells); // set the text/graphical displays that need to be updated
};

#endif