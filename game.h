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
    std::vector<bool> updated;

public:
    char getState(int row, int col) const override;
    static const int width = 8;
    static const int height = 8;
    Game(std::unique_ptr<Player> p1, std::unique_ptr<Player> p2);
    bool moveLink(Link *l, char dir);
    int whosTurn() override;
    virtual ~Game() override = default;
    std::unique_ptr<Player> &getPlayer(int index) override;
    char charAt(int i, int j) override; // should return "." if nothing in cell, and link char otherwise
    void initBoard();
    void initLinks();
    Link *getLinkFromID(char id, int player);
    void setUpdates(bool downloadedLinks, bool abilityCounter, bool knownLinks, bool cells); // set the text/graphical displays that need to be updated
    void attach(std::unique_ptr<Observer> o) override;                                       // from Subject
    void detach(Observer *o) override;
    void notifyObservers(Subject *whoFrom) override;
    void clearObservers() override;
};

#endif
