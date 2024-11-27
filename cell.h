#ifndef CELL_H
#define CELL_H
#include <memory>
#include "link.h"
#include "player.h"

class Cell
{
private:
    Cell(int t, int c);
    int row;
    int col;
    int isServerPort;           // return 1 for p1 and 2 for p2, 0 for not
    int isFirewall;             // return 1 for p1 and 2 for p2, 0 for not
    std::unique_ptr<Link> link; // owns the link while it is on the board (occupies a cell)
    Cell(int r, int c, bool sp = false, bool f = false, std::unique_ptr<Link> l = nullptr)
        : row(r), col(c), isServerPort(sp), isFirewall(f), link(std::move(l)) {}

public:
    static std::unique_ptr<Cell> create(int r, int c, bool sp, bool f, std::unique_ptr<Link> l = nullptr);
    int getRow() const;
    int getCol() const;
    int getIsServerPort() const;
    int getIsFirewall() const;
    bool isValid() const; // check the coordinates
    bool isEmpty() const; // check there's no server port, no firewall, and no link
    const std::unique_ptr<Link> &getLink() const;
    void setIsServerPort(int p);
    void setIsFirewall(int p);
    void setLink(std::unique_ptr<Link> l);
    void transferLinkToPlayer(Player &player); // transfers ownership of the link to the downloadedLinks vector in player
};

#endif
