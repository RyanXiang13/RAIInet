#include <iostream>
#include "textobserver.h"
#include "game.h"
#include "player.h"
#include "link.h"
#include "ability.h"

using namespace std;

TextObserver::TextObserver(bool twoPlayers) : twoPlayers{twoPlayers} {}

void TextObserver::notify(Subject &subject) {
  Game* game = dynamic_cast<Game*>(&subject);
  if (!game) return;
  auto& playerOne = game->getPlayer(0); //1st player
  auto& playerTwo = game->getPlayer(1); // 2nd player
  cout << "Player 1:" << endl;
  updateDownloaded(*playerOne);
  updateAbilityCounter(*playerOne);
  if (game->whosTurn() == 1) printOwnedLinks(*playerOne);
  else updateKnownLinks(*playerOne);
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
  else updateKnownLinks(*playerTwo);
}

void TextObserver::printOwnedLinks(Player& player) {
  const auto& ownedLinks = player.getOwnedLinks();
  int count = 1;
  for (const auto& link : ownedLinks) {
    cout << link->getID() << ": " << link->getName();
    if (count % 4 == 0) {
      cout << endl;
      count++;
      continue;
    }
    cout << " ";
    count ++;
  }

}

void TextObserver::displayWin(int winner) {
  if (winner == 1) {
    cout << "Player 1 wins!" << endl;
  } else if (winner == 2) {
    cout << "Player 2 wins!" << endl;
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
  const auto& knownLinks = player.getOwnedLinks();
  int count = 1;
  for (const auto& link : knownLinks) {
    cout << link->getID() << ": ";
    if (link->getIsFound()) {
      cout << link->getName();
    } else {
      cout << "?";
    }
    if (count % 4 == 0) {
      cout << endl;
      count++;
      continue;
    }
    cout << " ";
    count++;
  }
}

void TextObserver::displayAbilities(Player& player) {
  const auto& abilities = player.getAbilities();
  for (const auto& ability : abilities) {
    cout << ability->getID() << ". " << ability->getName();
    if (ability->isUsed()) {
      cout << " USED";
    }
    cout << endl;
  }
}

void TextObserver::displayWelcome() {
  cout << "Welcome to the game!" << endl;
}
