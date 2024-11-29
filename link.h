#ifndef LINK_H
#define LINK_H
#include "player.h"
#include "cell.h"
#include <memory>
#include <string>
#include <vector>

class Ability;
class Cell;
class Link
{
private:
    int row;
    int col;
    int strength;
    int moveStrength;
    bool isVirus;
    bool isFound;
    int playerID;
    char letterID;
    bool isDownloaded; // always check this first to see if the link is inactive
    std::vector<int> abilities;

public:
    Link(int r, int c, int s, int ms, bool v, char lid, int id, bool isD, std::vector<int> ab);
    static std::unique_ptr<Link> create(int r, int c, int s, int ms, bool v, char lid, int id, bool isD, std::vector<int> abilities = std::vector<int>(9, 0));
    int getRow() const;
    int getCol() const;
    int getStrength() const;
    int getMoveStrength() const;
    bool getIsVirus() const;
    bool hasAbility(int abilityID) const;
    bool getIsFound() const;
    int getPlayerID() const;
    bool getIsDownloaded() const;
    char getID() const;
    std::string getName() const; // create the name based on isVirus and strength
    void setRow(int r);
    void setCol(int c);
    void setStrength(int s);
    void setIsVirus(bool v);
    void setIsFound(bool f);
    void setPlayerID(int id);
    void setIsDownloaded(bool d);
    void addMoveStrength();
    void addAbility(int abilityID);
    void removeAbility(int abilityID);

    // special action cells functions
    bool isOnOpponentFirewall(std::vector<std::vector<std::unique_ptr<Cell>>> &board) const;
    bool isOnOpponentServerPort(std::vector<std::vector<std::unique_ptr<Cell>>> &board) const;
    bool isPastOpponentBoardEdge() const;

    // action functions
    void moveLink(char dir);
    bool battleLink(Link* l);
    bool onFirewall(std::vector<std::vector<std::unique_ptr<Cell>>> &board, std::vector<std::unique_ptr<Player>> &players);
};

#endif
