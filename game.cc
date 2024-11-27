#include "game.h"
#include "player.h"
#include "cell.h"
#include <vector>
#include <memory>

Game::Game(std::unique_ptr<Player> p1, std::unique_ptr<Player> p2) {
  players.emplace_back(p1);
  players.emplace_back(p2);
  board.resize(height);
  for (int i = 0; i < height; ++i) {
    board.resize(width);
    for (int j = 0; j < width; ++j) {
      board[i][j] = 
    }
  }
}