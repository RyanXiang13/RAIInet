#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <memory>
#include <string>
#include "link.h"

class Link;
class Ability;
class Player
{
private:
    Player(int id, bool isTurn, std::vector<std::unique_ptr<Ability>> a, std::vector<std::unique_ptr<Link>> l, int dD, int vD);
    int playerID;
    bool isTurn;
    std::vector<std::unique_ptr<Ability>> abilities;              // pointers to abilities
    std::vector<std::unique_ptr<Link>> ownedLinks;                // stores all names of links that the player owns              // stores all names of links that the player knows the opponent has
    int dataDownloaded;
    int virusDownloaded;

public:
    static std::unique_ptr<Player> create(int id, bool isTurn, std::vector<std::unique_ptr<Ability>> a = std::vector<std::unique_ptr<Ability>>(5, nullptr), std::vector<std::unique_ptr<Link>> l = std::vector<std::unique_ptr<Link>>(), int dataDownloaded = 0, int virusDownloaded = 0);
    int getPlayerID() const;
    bool getIsTurn() const;
    void setTurn(bool b);
    int getNumOfData() const;
    int getNumOfVirus() const;
    const std::vector<std::unique_ptr<Ability>> &getAbilities() const;
    const std::vector<std::unique_ptr<Link>> &getOwnedLinks() const;
    void addAbility(std::unique_ptr<Ability>);
    void download(Link* l);
    void addOwnedLink(std::unique_ptr<Link> l);
    int getAbilityCount() const;                        // returns the sum of array
};

#endif
