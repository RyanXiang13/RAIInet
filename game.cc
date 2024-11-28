#include "game.h"
#include "player.h"
#include "cell.h"
#
#include <vector>
#include <memory>
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

void Game::moveLink(Link* l, char dir) {
  int curRow = l->getRow();
  int curCol = l->getCol();
  l->moveLink(dir);
  if (l->getRow() > 7) {
    l->moveLink('U');
  } else if (l->getRow() < 0) {
    l->moveLink('D');
  } else if (l->getCol() > 7) {
    l->moveLink('L');
  } else if (l->getCol() < 0) {
    l->moveLink('R');
  } else if (board[l->getRow()][l->getCol()]->getLink() && board[l->getRow()][l->getCol()]->getLink()->getPlayerID() == l->getPlayerID()) {
    // move back to previous pos
  } else if (board[l->getRow()][l->getCol()]->getLink() && board[l->getRow()][l->getCol()]->getLink()->getPlayerID() != l->getPlayerID()) {
    /* CONFLICT RESOLUTION
    if(l->battleLink(board[l->getRow()][l->getCol()]->getLink())) {
      players[l->getPlayerID() - 1]->addDownloadedLink(board[l->getRow()][l->getCol()]->getLink());
      board[l->getRow()][l->getCol()]->setLink(l);
    }
    */
  } else {
    board[curRow][curCol]->setLink(nullptr);
    board[l->getRow()][l->getCol()]->setLink(l);
    notifyObservers(this);
  }
}
