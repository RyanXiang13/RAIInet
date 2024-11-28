#include "game.h"
#include "player.h"
#include "cell.h"
#include <vector>
#include <memory>
#include <algorithm>

Game::Game(std::unique_ptr<Player> p1, std::unique_ptr<Player> p2) {
  players.emplace_back(std::move(p1));
  players.emplace_back(std::move(p2));
  board.resize(height);
  for (int i = 0; i < height; ++i) {
    board.resize(width);
    for (int j = 0; j < width; ++j) {
      board[i][j] = Cell::create(i, j);
    }
  }
  const auto& p1Links = p1->getOwnedLinks();
  for (const auto& link : p1Links) {
    board[link->getRow()][link->getCol()]->setLink(link.get());
  }

  const auto& p2Links = p2->getOwnedLinks();
  for (const auto& link : p2Links) {
    board[link->getRow()][link->getCol()]->setLink(link.get());
  }

  board[0][3]->setIsServerPort(1);
  board[0][4]->setIsServerPort(1);
  board[7][3]->setIsServerPort(2);
  board[7][4]->setIsServerPort(2);

}

void moveLink(Link& l, char dir) {
  if (dir == 'U') {
    
  } else if (dir == 'D') {
    
  } else if (dir == 'L') {
    
  } else if (dir == 'R') {
    
  }
}

std::unique_ptr<Player>& Game::getPlayer(int index) {
  return players[index - 1];
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

/*
void Game::setUpdates(bool downloadedLinks, bool abilityCounter, bool knownLinks, bool cells) {
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      //board[row][col]->setIsUpdated(cells);
    }
  }
}
*/
