#include "game.h"
#include "player.h"
#include "cell.h"
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

bool Game::moveLink(Link* l, char dir) {
  int curRow = l->getRow();
  int curCol = l->getCol();
  /*
  if (!l->moveLink(dir)){
    return false;
  }
  */
  if (l->isOnOpponentServerPort(board)) {
    l->onServerPort(board, players);
  } else if (l->isOnOpponentFirewall(board)) {
    l->onFirewall(board, players);
  } else if (l->isPastOpponentBoardEdge(board)) {
    l->onPastBoardEdge(board, players);
  } else if (board[l->getRow()][l->getCol()]->getLink() && board[l->getRow()][l->getCol()]->getLink()->getPlayerID() == l->getPlayerID()) {
    l->setRow(curRow);
    l->setCol(curCol);
    return false;
  } else if (board[l->getRow()][l->getCol()]->getLink() && board[l->getRow()][l->getCol()]->getLink()->getPlayerID() != l->getPlayerID()) {
    // CONFLICT RESOLUTION
    if (l->battleLink(board[l->getRow()][l->getCol()]->getLink())) {
      players[l->getPlayerID() - 1]->download(board[l->getRow()][l->getCol()]->getLink());
      board[l->getRow()][l->getCol()]->setLink(l);
    } else {
      players[board[l->getRow()][l->getCol()]->getLink()->getPlayerID() - 1]->download(l);
    }
  } else {
    board[l->getRow()][l->getCol()]->setLink(l);
  }
  board[curRow][curCol]->setLink(nullptr);
  notifyObservers(this);
  players[0]->setTurn(!players[0]->getIsTurn());
  players[1]->setTurn(!players[1]->getIsTurn());

}
