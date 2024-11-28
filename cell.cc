#include "cell.h"
#include <memory>
#include "game.h"
#include "link.h"
#include "player.h"

std::unique_ptr<Cell> Cell::create(int r, int c, bool sp, bool f, Link* l)
{
    return std::make_unique<Cell>(r, c, sp, f, l);
}

int Cell::getRow() const
{
    return row;
}

int Cell::getCol() const
{
    return col;
}

int Cell::getIsServerPort() const
{
    return isServerPort;
}

int Cell::getIsFirewall() const
{
    return isFirewall;
}

const Link* Cell::getLink() const
{
    return link;
}

void Cell::setIsServerPort(int p)
{
    this->isServerPort = p;
}

void Cell::setIsFirewall(int p)
{
    this->isFirewall = p;
}

void Cell::setLink(Link* l)
{
    this->link = l;
}

bool Cell::isValid() const
{
    return this->row >= 0 && this->row < Game::height && this->col >= 0 && this->col < Game::width;
}

bool Cell::isEmpty() const
{
    return !this->isServerPort && !this->isFirewall && !this->link; // not a server port, not a firewall, and no link
}

void Cell::transferLinkToPlayer(Player &player)
{
    player.addDownloadedLink(std::unique_ptr<Link>(this->link)); // transfer ownership of link to player once its been downloaded
    this->link = nullptr;                            // already done in previous step but just for certain
}
