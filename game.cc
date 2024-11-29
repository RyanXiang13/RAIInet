#include "game.h"
#include "player.h"
#include "cell.h"
#include "link.h"
#include "ability.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

Game::Game(std::unique_ptr<Player> p1, std::unique_ptr<Player> p2)
{
    players.emplace_back(std::move(p1));
    players.emplace_back(std::move(p2));
    board.resize(height);
    for (int i = 0; i < height; ++i)
    {
        board[i].resize(width);
        for (int j = 0; j < width; ++j)
        {
            board[i][j] = Cell::create(i, j);
        }
    }

    auto &p1Links = players[0]->getOwnedLinks();
    for (const auto &link : p1Links)
    {
        board[link->getRow()][link->getCol()]->setLink(link.get());
    }

    const auto &p2Links = players[1]->getOwnedLinks();
    for (const auto &link : p2Links)
    {
        board[link->getRow()][link->getCol()]->setLink(link.get());
    }

    board[0][3]->setIsServerPort(1);
    board[0][4]->setIsServerPort(1);
    board[7][3]->setIsServerPort(2);
    board[7][4]->setIsServerPort(2);
}

std::unique_ptr<Player> &Game::getPlayer(int index)
{
    return players[index];
}

char Game::charAt(int i, int j)
{
    if (board[i][j]->isEmpty())
    {
        return '.';
    }
    else if (board[i][j]->getIsServerPort() != 0)
    {
        return 'S';
    }
    else if (board[i][j]->getIsFirewall() && board[i][j]->getLink()) // FIX
    {
      return board[i][j]->getLink()->getID();
    }
    else if (board[i][j]->getIsFirewall() == 1)
    {
        return 'm';
    }
    else if (board[i][j]->getIsFirewall() == 2)
    {
        return 'w';
    }
    else
    {
      return board[i][j]->getLink()->getID();
    }
}

int Game::whosTurn()
{
    if (players[0]->getIsTurn())
        return 1;
    if (players[1]->getIsTurn())
        return 2;
    return 1;
}

int Game::notTurn() {
  if (players[0]->getIsTurn()) {
    return 2;
  }
  if (players[1]->getIsTurn()) {
    return 1;
  }
  return 2;
}

bool Game::moveLink(Link *l, char dir)
{
    int curRow = l->getRow();
    int curCol = l->getCol();
    l->moveLink(dir);
    if (l->isPastOpponentBoardEdge())
    {
        l->setIsFound(true);
        players[l->getPlayerID() - 1]->download(l); // owner downloads
    }
    else if (l->isOnOpponentServerPort(board))
    {
        l->setIsFound(true);
        players[l->getPlayerID() % 2]->download(l); // opponent downloads
    }
    else if (l->isOnOpponentFirewall(board))
    {
        l->setIsFound(true);
        if (l->getIsVirus())
        {
          players[l->getPlayerID() - 1]->download(l);
        } 
        else if (board[l->getRow()][l->getCol()]->getLink() && board[l->getRow()][l->getCol()]->getLink()->getPlayerID() != l->getPlayerID())
        {
          // CONFLICT RESOLUTION
          l->setIsFound(true);
          board[l->getRow()][l->getCol()]->getLink()->setIsFound(true);
          if (l->battleLink(board[l->getRow()][l->getCol()]->getLink()))
          {
            players[l->getPlayerID() - 1]->download(board[l->getRow()][l->getCol()]->getLink());
            board[l->getRow()][l->getCol()]->setLink(l);
          }
          else
          {
            players[board[l->getRow()][l->getCol()]->getLink()->getPlayerID() - 1]->download(l);
          }
        } else {
          board[l->getRow()][l->getCol()]->setLink(l);
        }
    }
    else if (board[l->getRow()][l->getCol()]->getLink() && board[l->getRow()][l->getCol()]->getLink()->getPlayerID() == l->getPlayerID())
    {
        l->setRow(curRow);
        l->setCol(curCol);
        return false;
    }
    else if (board[l->getRow()][l->getCol()]->getIsServerPort() == l->getPlayerID())
    {
      l->setRow(curRow);
      l->setCol(curCol);
      return false;
    } else if (board[l->getRow()][l->getCol()]->getLink() && board[l->getRow()][l->getCol()]->getLink()->getPlayerID() != l->getPlayerID())
    {
        // CONFLICT RESOLUTION
        l->setIsFound(true);
        board[l->getRow()][l->getCol()]->getLink()->setIsFound(true);
        if (l->battleLink(board[l->getRow()][l->getCol()]->getLink()))
        {
            players[l->getPlayerID() - 1]->download(board[l->getRow()][l->getCol()]->getLink());
            board[l->getRow()][l->getCol()]->setLink(l);
        }
        else
        {
            players[board[l->getRow()][l->getCol()]->getLink()->getPlayerID() - 1]->download(l);
        }
    }
    else
    {
        board[l->getRow()][l->getCol()]->setLink(l);
    }
    std::cout << curRow << curCol << std::endl;
    board[curRow][curCol]->setLink(nullptr);
    int currentPlayer = l->getPlayerID() - 1;
    players[currentPlayer]->setTurn(false);
    players[1 - currentPlayer]->setTurn(true);
    notifyObservers(this);
    return true;
}

Link *Game::getLinkFromID(char id, int player)
{

    const auto &pLinks = players[player - 1]->getOwnedLinks();
    for (const auto &link : pLinks)
    {
        if (link->getID() == id)
            return link.get();
    }
    return nullptr;
}

void Game::attach(std::unique_ptr<Observer> o)
{
    observers.push_back(std::move(o));
}

void Game::detach(Observer *o)
{
    auto it = std::find_if(observers.begin(), observers.end(),
                           [o](const std::unique_ptr<Observer> &up)
                           {
                               return up.get() == o;
                           });
    if (it != observers.end())
    {
        observers.erase(it);
    }
}

void Game::notifyObservers(Subject *whoFrom)
{
    for (auto &ob : observers)
    {
        ob->notify(*whoFrom);
    }
}

char Game::getState(int row, int col) const
{
    if (board[row][col]->isEmpty())
    {
        return '.';
    }
    else if (board[row][col]->getIsServerPort() != 0)
    {
        return 'S';
    }
    else if (board[row][col]->getIsFirewall() == 1)
    {
        return 'm';
    }
    else if (board[row][col]->getIsFirewall() == 2)
    {
        return 'w';
    }
    else
    {
        return board[row][col]->getLink()->getID();
    }
}

void Game::clearObservers()
{
    observers.clear();
}

bool Game::useAbility(int a, int pID) {
  const auto& abilities = players[pID - 1]->getAbilities();
  for (const auto& ability : abilities) {
    if (ability->getID() == a && !ability->isUsed()) {
      bool result = ability->use(pID, this);  // Return the result of use()
      notifyObservers(this);
      return result;
    }
  }
  notifyObservers(this);
  return false;
}

Cell* Game::getCell(int row, int col) {
  return board[row][col].get();
}
