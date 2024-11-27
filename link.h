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
    int moveStrength;
    bool isVirus;
    int playerID;
    bool isDownloaded; // always check this first to see if the link is inactive
    std::vector<int> abilities;
    Link(int r, int c, bool v, bool o, bool h, bool d, int id, bool isD);

public:
    static std::unique_ptr<Link> create(int r, int c, int s, bool v, bool pID, bool isD, std::vector<int> abilities = std::vector<int>(9, 0));
    int getRow() const;
    int getCol() const;
    int getStrength() const;
    int getMoveStrength() const;
    bool getIsVirus() const;
    bool hasAbility(int abilityID) const;
    int getPlayerID() const;
    bool getIsDownloaded() const;
    char getId() const;
    std::string getName() const; // create the name based on isVirus and strength
    void setRow(int r);
    void setCol(int c);
    void setStrength(int s);
    void addMoveStrength();
    void setIsVirus(bool v);
    void setPlayerID(int id);
    void setIsDownloaded(bool d);
    void addAbility(int abilityID);
    void removeAbility(int abilityID);

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
