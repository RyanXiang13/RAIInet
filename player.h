#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <memory>
#include <string>
#include "link.h"
#include "ability.h"

class Player
{
private:
    Player(int id, std::vector<std::unique_ptr<Ability>> a, std::vector<std::unique_ptr<Link>> ol, std::vector<std::unique_ptr<Link>> kl, std::vector<std::unique_ptr<Link>> dl);
    int playerID;
    std::vector<int> abilities;                         // stores all counts of abilities, 0 is ignored and 1-8 are the IDs, respectively
    std::vector<std::unique_ptr<Link>> ownedLinks;      // stores all owned link objects
    std::vector<std::string> knownLinks;                // stores all link objects that the player knows the opponent has
    std::vector<std::unique_ptr<Link>> downloadedLinks; // stores all link objects that the player has downloaded

public:
    static std::unique_ptr<Player> create(int id, std::vector<int> a = std::vector<int>(5, 9), std::vector<std::unique_ptr<Link>> l = std::vector<std::unique_ptr<Link>>(), std::vector<std::string> kl = std::vector<std::string>(), std::vector<std::unique_ptr<Link>> dl = std::vector<std::unique_ptr<Link>>());
    int getPlayerID() const;
    const std::vector<int> &getAbilities() const;
    const std::vector<std::unique_ptr<Link>> &getOwnedLinks() const;
    const std::vector<std::unique_ptr<Link>> &getKnownLinks() const;
    const std::vector<std::unique_ptr<Link>> &getDownloadedLinks() const;
    void addAbility(int a);
    void addOwnedLink(std::unique_ptr<Link> l);
    void addKnownLink(std::string s);
    void addDownloadedLink(std::unique_ptr<Link> l);
    void removeAbility(int a); // removes one count of the ability from the corresponding index
    void removeOwnedLink(std::unique_ptr<Link> l);
    void removeKnownLink(std::string s);                // unsure if this is needed as there is no way to remove a known link
    void removeDownloadedLink(std::unique_ptr<Link> l); // unsure if this is needed as there is no way to remove a downloaded link
    bool hasAbility(int a) const;
    int getAbilityCount() const;
};

#endif;
