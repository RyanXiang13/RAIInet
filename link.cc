#include "link.h"
#include <memory>
#include <string>
#include <vector>
#include "game.h"
#include "player.h"
#include "firewall.h"

Link::Link(int r, int c, int s, int ms, bool v, char lid, int id, bool isD, std::vector<int> abilities) {
    row = r;
    col = c;
    strength = s;
    moveStrength = ms;
    isVirus = v;
    letterID = lid;
    playerID = id;
    isDownloaded = isD;
    this->abilities = abilities;
}

bool Link::getIsFound() const {
    return isFound; 
}

std::unique_ptr<Link> Link::create(int r, int c, int s, int ms, bool v, char lid, int id, bool isD, std::vector<int> abilities)
{
    return std::unique_ptr<Link>(new Link(r, c, s, ms, v, lid, id, isD, abilities));
}

int Link::getRow() const
{
    return row;
}

int Link::getCol() const
{
    return col;
}

int Link::getStrength() const
{
    return strength;
}

int Link::getMoveStrength() const
{
    return moveStrength;
}

bool Link::getIsVirus() const
{
    return isVirus;
}

int Link::getPlayerID() const
{
    return playerID;
}

bool Link::getIsDownloaded() const
{
    return isDownloaded;
}

char Link::getID() const {
    return letterID;
}

std::string Link::getName() const
{
    std::string name = "";
    if (isVirus)
    {
        name += "V";
    }
    else
    {
        name += "D";
    }
    name += std::to_string(strength);
    return name;
}

void Link::setRow(int r)
{
    this->row = r;
}

void Link::setCol(int c)
{
    this->col = c;
}

void Link::setStrength(int s)
{
    this->strength = s;
}

void Link::setIsVirus(bool v)
{
    this->isVirus = v;
}

void Link::setPlayerID(int id)
{
    this->playerID = id;
}

void Link::setIsFound(bool f) {
    isFound = f;
}

void Link::setIsDownloaded(bool d)
{
    this->isDownloaded = d;
}

void Link::addMoveStrength()
{
    this->moveStrength++;
}

void Link::addAbility(int abilityID)
{
    this->abilities[abilityID]++;
}

void Link::removeAbility(int abilityID)
{
    this->abilities[abilityID]--;
}

bool Link::hasAbility(int abilityID) const
{
    return this->abilities[abilityID] > 0; // as long as there are at least 1
}

bool Link::isOnOpponentFirewall(std::vector<std::vector<std::unique_ptr<Cell>>> &board) const
{
    // check if the cell the link is on has an opponent's firewall
    if (board[this->row][this->col]->getIsServerPort() != 0 && board[this->row][this->col]->getIsFirewall() != this->playerID)
    { // must be on the opposite player's firewall to mean anything
        return true;
    }
    return false;
}

bool Link::isOnOpponentServerPort(std::vector<std::vector<std::unique_ptr<Cell>>> &board) const
{
    // check if the cell the link is on has one of the opposing player's server ports
    if (board[this->row][this->col]->getIsServerPort() != 0 && board[this->row][this->col]->getIsServerPort() != this->playerID)
    { // must be on the opposite player's server port to mean anything
        return true;
    }
    return false;
}

bool Link::isPastOpponentBoardEdge(std::vector<std::vector<std::unique_ptr<Cell>>> &board) const
{
    // check if the link has moved past the opposing player's board edge
    if (this->playerID == 1)
    { // must move past top edge (row 0) and not the bottom edge
        return this->row < 0;
    }
    // must move past the bottom edge (row Game::height - 1) and not the top edge
    return this->row > Game::height - 1;
}

void Link::moveLink(char dir)
{
    // note this function simply moves it, validaton regarding the move is done in the game class
    if (dir == 'U')
    {
        this->row -= this->moveStrength;
    }
    else if (dir == 'D')
    {
        this->row += this->moveStrength;
    }
    else if (dir == 'L')
    {
        this->col -= this->moveStrength;
    }
    else if (dir == 'R')
    {
        this->col += this->moveStrength;
    }
}

bool Link::battleLink( Link* l)
{                                         // returns true if the initiating player's link wins the battle
    return this->strength >= l->strength; // initiator wins if their strength is equal as well
}

bool Link::onFirewall(std::vector<std::vector<std::unique_ptr<Cell>>> &board, std::vector<std::unique_ptr<Player>> &players)
{
    // simply call the activate firewall function
    return Firewall::activate(*this, *board[this->row][this->col], players);
}

