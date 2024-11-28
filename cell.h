#ifndef CELL_H
#define CELL_H
#include <memory>
#include "link.h"
#include "player.h"

class Link;
class Player;

class Cell
{
private:
    Cell(int t, int c);
    int row;
    int col;
    int isServerPort;           // return 1 for p1 and 2 for p2, 0 for not
    int isFirewall;             // return 1 for p1 and 2 for p2, 0 for not
    Link* link; // owns the link while it is on the board (occupies a cell)
    Cell(int r, int c, bool sp = false, bool f = false, Link* l = nullptr)
        : row(r), col(c), isServerPort(sp), isFirewall(f), link(l) {}

public:
    static std::unique_ptr<Cell> create(int r, int c, bool sp = false, bool f = false, Link* l = nullptr);
    int getRow() const;
    int getCol() const;
    int getIsServerPort() const;
    int getIsFirewall() const;
    bool isValid() const; // check the coordinates
    bool isEmpty() const; // check there's no server port, no firewall, and no link
    Link* getLink() const;
    void setIsServerPort(int p);
    void setIsFirewall(int p);
    void setLink(Link* l);
    void transferLinkToPlayer(Player &player); // transfers ownership of the link to the downloadedLinks vector in player
};

#endif
