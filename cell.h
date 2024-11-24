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
    int isSeverPort; // return 1 for p1 and 2 for p2
    int isFirewall;  // return 1 for p1 and 2 for p2
    int isEdge;      // return 0 for not edge, 1 for p1 and 2 for p2
    std::unique_ptr<Link> link;

public:
    static std::unique_ptr<Cell> create(int r, int c, bool sp, bool f, std::unique_ptr<Link> l = nullptr);
    int getRow() const;
    int getCol() const;
    int isSeverPort() const;
    int isFirewall() const;
    int isEdge() const;
    const std::unique_ptr<Link> &getLink() const;
    void setLink(std::unique_ptr<Link> l);
};

#endif