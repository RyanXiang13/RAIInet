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
    bool hasAbility;
    int playerID;
    bool isDownloaded; // always check this first to see if the link is inactive
    std::vector<std::unique_ptr<Ability>> abilities;
    Link(int r, int c, bool v, bool o, bool h, bool d, int id, bool isD);

public:
    static std::unique_ptr<Link> create(int r, int c, bool v, bool o, bool h, int id, bool isD);
    int getRow() const;
    int getCol() const;
    int getStrength() const;
    bool getIsVirus() const;
    bool getHasAbility() const;
    int getPlayerID() const;
    bool getIsDownloaded() const;
    std::string getName() const; // create the name based on isVirus and strength
    void setRow(int r);
    void setCol(int c);
    void setStrength(int s);
    void setIsVirus(bool v);
    void setHasAbility(bool h);
    void setPlayerID(int id);
    void setIsDownloaded(bool d);

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