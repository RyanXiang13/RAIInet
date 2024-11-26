#ifndef CELL_H
#define CELL_H
#include "ability.h"
#include "link.h"
#include <memory>

class Cell
{
private:
    Cell(int t, int c);
    int row;
    int col;
    int isSeverPort;            // return 1 for p1 and 2 for p2
    int isFirewall;             // return 1 for p1 and 2 for p2
    int isTopOrBottomEdge;      // return 0 for not edge, 1 for p1 and 2 for p2
    std::unique_ptr<Link> link; // owns the link while it is on the board (occupies a cell)

public:
    static std::unique_ptr<Cell> create(int r, int c, bool sp, bool f, std::unique_ptr<Link> l = nullptr);
    int getRow() const;
    int getCol() const;
    int getIsServerPort() const;
    int getIsFirewall() const;
    int getIsTopOrBottomEdge() const;
    bool isValid() const; // check the coordinates
    bool isEmpty() const; // check there's no server port, no firewall, and no link
    const std::unique_ptr<Link> &getLink() const;
    void setIsServerPort(int p);
    void setIsFirewall(int p);
    void setIsTopOrBottomEdge(int p);
    void setLink(std::unique_ptr<Link> l);
};

#endif
