#include <iostream>
#include "textobserver.h"
#include "game.h"
using namespace std;

TextObserver::TextObserver(bool twoPlayers) : twoPlayers{twoPlayers} {}

void TextObserver::notify(Subject &subject) {
  Game* game = dynamic_cast<Game*>(&subject);
  if (!game) return;
  std::unique_ptr<Player> playerOne = game->getPlayer(0); //1st player
  std::unique_ptr<Player> playerTwo = game->getPlayer(1); // 2nd player
  cout << "Player 1:" << endl;
  updateDownloaded(*playerOne);
  updateAbilityCounter(*playerOne);
  if (game->whosTurn() == 1) printOwnedLinks(*playerOne);
  else updateKnownLinks(*playerTwo);
  for (int i = 0; i < WIDTH; i++) {
    cout << "=";
  }
  cout << endl;
  for (int i = 0; i < LENGTH; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      cout << game->charAt(i, j);
    }
    cout << endl;
  }
  for (int i = 0; i < WIDTH; i++) {
    cout << "=";
  }
  cout << endl << "Player 2:" << endl;
  updateDownloaded(*playerTwo);
  updateAbilityCounter(*playerTwo);
  if (game->whosTurn() == 2) printOwnedLinks(*playerTwo);
  else updateKnownLinks(*playerOne);
}

void TextObserver::printOwnedLinks(Player& player) {
  const auto& ownedLinks = player.getOwnedLinks();
  int count = 0;
  for (const auto& link : ownedLinks) {
    cout << link->getId() << ": " << link->getName();
    if (count % 4 == 0) {
      cout << endl;
      continue;
    }
    cout << " ";
  }

}
void TextObserver::updateDownloaded(Player& player) {
  cout << "Downloaded: " << player.getNumOfData() << "D, " 
    << player.getNumOfVirus() << "V" << endl;
}

void TextObserver::updateAbilityCounter(Player& player) {
  cout << "Abilities: " << player.getAbilityCount() << endl;
}

void TextObserver::updateKnownLinks(Player& player) {
  const auto& knownLinks = player.getKnownLinks();
  char start;
  int count = 0;
  if (player.getPlayerID() == 1) {
  start = 65; // player two has upper casse A to start
  } else {
  start = 97; // lowercase a to start if player two
  }
  for (const auto& link : knownLinks) {
    cout << start << ": ";
    start++;
    cout << link->getName();
    if (count % 4 == 0) {
      cout << endl;
      continue;
    }
    cout << link->getStrength() << " ";
  }
}