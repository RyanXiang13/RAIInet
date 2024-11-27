#include <iostream>
#include "textobserver.h"
#include "game.h"
using namespace std;

TextObserver::TextObserver(bool twoPlayers) : twoPlayers{twoPlayers} {}

void TextObserver::notify(Subject &game) {
  cout << "Player 1:" << endl;
  updateDownloaded(1);
  updateAbilityCounter(1);
  if (game.whosTurn() == 1) printOwnedLinks(1);
  else updateKnownLinks(2);
  for (int i = 0; i < WIDTH; i++) {
    cout << "=";
  }
  cout << endl;
  for (int i = 0; i < LENGTH; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      cout << game.charAt(i, j);
    }
    cout << endl;
  }
  for (int i = 0; i < WIDTH; i++) {
    cout << "=";
  }
  cout << endl << "Player 2:" << endl;
  updateDownloaded(2);
  updateAbilityCounter(2);
  if (game.whosTurn() == 2) printOwnedLinks(2);
  else updateKnownLinks(1);
}