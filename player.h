#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <memory>
#include "link.h"
#include "ability.h"

class Player
{
private:
    Player(int id, std::vector<std::unique_ptr<Ability>> a, std::vector<std::unique_ptr<Link>> ol, std::vector<std::unique_ptr<Link>> kl, std::vector<std::unique_ptr<Link>> dl);
    int playerID;
    std::vector<std::unique_ptr<Ability>> abilities;    // stores all ability objects
    std::vector<std::unique_ptr<Link>> ownedLinks;      // stores all owned link objects
    std::vector<std::unique_ptr<Link>> knownLinks;      // stores all link objects that the player knows the opponent has
    std::vector<std::unique_ptr<Link>> downloadedLinks; // stores all link objects that the player has downloaded

public:
    static std::unique_ptr<Player> create(int id, std::vector<std::unique_ptr<Ability>> a, std::vector<std::unique_ptr<Link>> l, std::vector<std::unique_ptr<Link>> kl, std::vector<std::unique_ptr<Link>> dl);
    int getPlayerID() const;
    const std::vector<std::unique_ptr<Ability>> &getAbilities() const;
    const std::vector<std::unique_ptr<Link>> &getOwnedLinks() const;
    const std::vector<std::unique_ptr<Link>> &getKnownLinks() const;
    const std::vector<std::unique_ptr<Link>> &getDownloadedLinks() const;
    void addAbility(std::unique_ptr<Ability> a);
    void addOwnedLink(std::unique_ptr<Link> l);
    void addKnownLink(std::unique_ptr<Link> l);
    void addDownloadedLink(std::unique_ptr<Link> l);
    void removeAbility(std::unique_ptr<Ability> a);
    void removeOwnedLink(std::unique_ptr<Link> l);
    void removeKnownLink(std::unique_ptr<Link> l);      // unsure if this is needed as there is no way to remove a known link
    void removeDownloadedLink(std::unique_ptr<Link> l); // unsure if this is needed as there is no way to remove a downloaded link
};

#endif