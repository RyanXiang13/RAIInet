#include "game.h"
#include "player.h"
#include "cell.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

Game::Game(std::unique_ptr<Player> p1, std::unique_ptr<Player> p2) {
  players.emplace_back(std::move(p1));
  players.emplace_back(std::move(p2));
  board.resize(height);
  for (int i = 0; i < height; ++i) {
    board[i].resize(width);
    for (int j = 0; j < width; ++j) {
      board[i][j] = Cell::create(i, j);
    }
  }

  auto& p1Links = players[0]->getOwnedLinks();
  for (const auto& link : p1Links) {
  board[link->getRow()][link->getCol()]->setLink(link.get());
  }

  const auto& p2Links = players[1]->getOwnedLinks();
  for (const auto& link : p2Links) {
    board[link->getRow()][link->getCol()]->setLink(link.get());
  }

  board[0][3]->setIsServerPort(1);
  board[0][4]->setIsServerPort(1);
  board[7][3]->setIsServerPort(2);
  board[7][4]->setIsServerPort(2);
}

bool Game::moveLink(Link* l, char dir) {
    if (dir == 'U') {
        // implementation
    } else if (dir == 'D') {
        // implementation
    } else if (dir == 'L') {
        // implementation
    } else if (dir == 'R') {
        // implementation
    }
    return true; // or false depending on if move was successful
}

std::unique_ptr<Player>& Game::getPlayer(int index) {
  return players[index];
}

char Game::charAt(int i, int j) {
  if (board[i][j]->isEmpty()) {
    return '.';
  } else if (board[i][j]->getIsServerPort() != 0) {
    return 'S';
  } else if (board[i][j]->getIsFirewall() == 1) {
    return 'm';
  } else if (board[i][j]->getIsFirewall() == 2) {
    return 'w';
  } else {
    return board[i][j]->getLink()->getID();
  }
}

int Game::whosTurn() {
  for (size_t i = 0; i < players.size(); ++i) {
    if (players[i]->getIsTurn()) {
      return i + 1;
    }
  }
  return 1; // default to player 1 for testing
}

char Game::getState(int row, int col) const {
    if (board[row][col]->isEmpty()) {
        return '.';
    } else if (board[row][col]->getIsServerPort() != 0) {
        return 'S';
    } else if (board[row][col]->getIsFirewall() == 1) {
        return 'm';
    } else if (board[row][col]->getIsFirewall() == 2) {
        return 'w';
    } else {
        return board[row][col]->getLink()->getID();
    }
}

void Game::attach(std::unique_ptr<Observer> o) {
    observers.push_back(std::move(o));
}

void Game::detach(Observer* o) {
    auto it = std::find_if(observers.begin(), observers.end(),
                          [o](const std::unique_ptr<Observer>& up) {
                              return up.get() == o;
                          });
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void Game::notifyObservers(Subject* whoFrom) {
    for (auto& ob : observers) {
        ob->notify(*whoFrom);
    }
}
