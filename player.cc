#include "player.h"
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "link.h"
#include "ability.h"

std::unique_ptr<Player> Player::create(int id, bool isTurn, std::vector<std::unique_ptr<Ability>> a, std::vector<std::unique_ptr<Link>> l, int dD, int vD) {
    return std::unique_ptr<Player>(new Player(id, isTurn, std::move(a), std::move(l), dD, vD)); // Use std::move for unique_ptr
}

int Player::getPlayerID() const
{
    return playerID;
}

bool Player::getIsTurn() const
{
    return isTurn;
}

const std::vector<std::unique_ptr<Ability>> &Player::getAbilities() const
{
    return abilities;
}

const std::vector<std::unique_ptr<Link>> &Player::getOwnedLinks() const
{
    return ownedLinks;
}

void Player::setTurn(bool b)
{
    this->isTurn = b; // true for it is the current player's turn, note that at any given time the two player's isTurn values should be opposite to each other
}

void Player::addAbility(std::unique_ptr<Ability> a)
{
    this->abilities.push_back(std::move(a)); // add one count of the ability to the corresponding index
}

void Player::addOwnedLink(std::unique_ptr<Link> l)
{
    this->ownedLinks.push_back(std::move(l)); // add the name of the link as we only want one owner for unique pointers (and that is downloadedLinks)
}
/*
void Player::removeAbility(int a)
{
    this->abilities[a]--; // remove one count of the ability from the corresponding index
}


void Player::removeOwnedLink(std::string s)
{
    // this may or may not be needed when one of the players loses their link
    std::vector<std::string>::iterator it = std::find(this->ownedLinks.begin(), this->ownedLinks.end(), s);
    if (it != this->ownedLinks.end()) // if the link is found
    {
        this->ownedLinks.erase(it); // simply delete the link name from the vector
    }
}


bool Player::useAbility(int a) const
{
    for (const auto& ability : abilities) {
        if (ability->getID() == a && !ability->isUsed()) {
            ability->use();
        }
    }
}
*/
int Player::getAbilityCount() const
{
    int sum = 0;
    for (const auto& ability : abilities)
    {
        if (!ability->isUsed()) sum++;
    }
    return sum;
}

// Constructor implementation
Player::Player(int id, bool isTurn, std::vector<std::unique_ptr<Ability>> a, std::vector<std::unique_ptr<Link>> l, 
            int dD, int vD) {
    playerID = id;
    this->isTurn = isTurn;
    abilities = std::move(a);
    ownedLinks = std::move(l);
    dataDownloaded = dD;
    virusDownloaded = vD;
}

// Missing methods
int Player::getNumOfData() const {
    return dataDownloaded;
}

int Player::getNumOfVirus() const {
    return virusDownloaded;
}

void Player::download(Link* l) {
    if (!l) return;
    l->setIsDownloaded(true);
    l->setIsFound(true);
    if (l->getIsVirus()) {
        virusDownloaded++;
    } else {
        dataDownloaded++;
    }
}
