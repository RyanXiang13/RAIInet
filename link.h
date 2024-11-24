#ifndef LINK_H
#define LINK_H
#include "player.h"
#include <memory>

class Link
{
private:
    int row;
    int col;
    int strength;
    bool isVirus;
    bool isOccupied;
    bool hasAbility;
    int playerID;
    bool isDownloaded;
    Link(int r, int c, bool v, bool o, bool h, bool d, int id, bool isD);

public:
    static std::unique_ptr<Link> create(int r, int c, bool v, bool o, bool h, int id, bool isD);
    int getRow() const;
    int getCol() const;
    int getStrength() const;
    bool isVirus() const;
    bool isOccupied() const;
    bool hasAbility() const;
    int getPlayerID() const;
    bool isDownloaded() const;
    void setRow(int r);
    void setCol(int c);
    void setStrength(int s);
    void setVirus(bool v);
    void setOccupied(bool o);
    void setHasAbility(bool h);
    void setPlayerID(int id);
    void setDownloaded(bool d);

    // special action cells functions
    bool isOnFirewall() const;
    bool isOnServerPort() const;
    bool isPastBoardEdge() const;

    // action functions
    void moveLink(char dir);
    bool battleLink(std::unique_ptr<Link> l);
    void onServerPort();
    void onFirewall();
    void onPastBoardEdge();
};

#endif