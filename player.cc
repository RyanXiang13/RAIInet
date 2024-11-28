#include "player.h"
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "link.h"
#include "ability.h"

std::unique_ptr<Player> Player::create(int id, bool isTurn, std::vector<int> a, std::vector<std::unique_ptr<Link>> l, std::vector<std::string> kl, std::vector<std::unique_ptr<Link>> dl) {
    return std::unique_ptr<Player>(new Player(id, isTurn, a, std::move(l), kl, std::move(dl))); // Use std::move for unique_ptr
}

int Player::getPlayerID() const
{
    return playerID;
}

bool Player::getIsTurn() const
{
    return isTurn;
}

const std::vector<int> &Player::getAbilities() const
{
    return abilities;
}

const std::vector<std::unique_ptr<Link>> &Player::getOwnedLinks() const
{
    return ownedLinks;
}

const std::vector<std::string> &Player::getKnownLinks() const
{
    return knownLinks;
}

const std::vector<std::unique_ptr<Link>> &Player::getDownloadedLinks() const
{
    return downloadedLinks;
}

void Player::setTurn(bool b)
{
    this->isTurn = b; // true for it is the current player's turn, note that at any given time the two player's isTurn values should be opposite to each other
}

void Player::addAbility(int a)
{
    this->abilities[a]++; // add one count of the ability to the corresponding index
}

void Player::addOwnedLink(std::unique_ptr<Link> l)
{
    this->ownedLinks.push_back(std::move(l)); // add the name of the link as we only want one owner for unique pointers (and that is downloadedLinks)
}

void Player::addKnownLink(std::string s)
{
    this->knownLinks.push_back(s); // add the name of the link as we only want one owner for unique pointers (and that is downloadedLinks)
}

void Player::addDownloadedLink(std::unique_ptr<Link> l)
{
    this->downloadedLinks.push_back(std::move(l));
}

void Player::removeAbility(int a)
{
    this->abilities[a]--; // remove one count of the ability from the corresponding index
}

/*
void Player::removeOwnedLink(std::string s)
{
    // this may or may not be needed when one of the players loses their link
    std::vector<std::string>::iterator it = std::find(this->ownedLinks.begin(), this->ownedLinks.end(), s);
    if (it != this->ownedLinks.end()) // if the link is found
    {
        this->ownedLinks.erase(it); // simply delete the link name from the vector
    }
}
*/

void Player::removeKnownLink(std::string s)
{
    // unsure if this is needed as there is no way to un-know a link but just in case
    std::vector<std::string>::iterator it = std::find(this->knownLinks.begin(), this->knownLinks.end(), s);
    if (it != this->knownLinks.end()) // if the link is found
    {
        this->knownLinks.erase(it); // simply delete the link name from the vector
    }
}

void Player::removeDownloadedLink(std::unique_ptr<Link> l)
{
    // unsure if this is needed as there should be no way to un-download a link
    std::vector<std::unique_ptr<Link>>::iterator it = std::find(this->downloadedLinks.begin(), this->downloadedLinks.end(), l);
    if (it != this->downloadedLinks.end()) // if the link is found
    {
        this->downloadedLinks.erase(it); // simply delete the link from the vector
    }
}

bool Player::hasAbility(int a) const
{
    return this->abilities[a] > 0; // true if the ability is greater than 0 (i.e. the player has at least 1 of the ability)
}

int Player::getAbilityCount() const
{
    int sum = 0;
    for (int i : abilities)
    {
        sum += i;
    }
    return sum;
}

// Constructor implementation
Player::Player(int id, bool isTurn, std::vector<int> a, std::vector<std::unique_ptr<Link>> l, 
              std::vector<std::string> kl, std::vector<std::unique_ptr<Link>> dl) {
    playerID = id;
    this->isTurn = isTurn;
    abilities = a;
    ownedLinks = std::move(l);
    knownLinks = kl;
    downloadedLinks = std::move(dl);
}

// Missing methods
int Player::getNumOfData() const {
    int count = 0;
    for (const auto& link : downloadedLinks) {
        if (!link->getIsVirus()) count++;
    }
    return count;
}

int Player::getNumOfVirus() const {
    int count = 0;
    for (const auto& link : downloadedLinks) {
        if (link->getIsVirus()) count++;
    }
    return count;
}
