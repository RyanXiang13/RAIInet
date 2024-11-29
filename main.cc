#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <sstream>
#include <random>
#include <algorithm>
#include "game.h"
#include "player.h"
#include "link.h"
#include "ability.h"
#include "textobserver.h"
#include "graphicsobserver.h"
#include "buff.h"
#include "download.h"
#include "scan.h"
#include "firewall.h"
#include "polarize.h"
#include "linkboost.h"
#include "teleport.h"
#include "skipturn.h"

using namespace std;

int main(int argc, char* argv[])
{
  string p1AbilityOrder = "LFDSP"; // default for player 1
  string p2AbilityOrder = "FDSPL"; // default for player 2
  vector<string> p1LinkOrder;
  vector<string> p2LinkOrder;
  bool includeGraphics = false;
  bool link1Passed = false;
  bool link2Passed = false;
  // parse command-line arguments
  for (int i = 1; i < argc; ++i) {
    if (string(argv[i]) == "-ability1" && i + 1 < argc) { // specify player 1 abilities
      p1AbilityOrder = argv[++i]; // store the 5 letter string
    } else if (string(argv[i]) == "-ability2" && i + 1 < argc) { // specify player 2 abilities
      p2AbilityOrder = argv[++i]; // store the 5 letter string
    } else if (string(argv[i]) == "-link1" && i + 1 < argc) { // specify player 1 links
        // load links from custom file for player 1
        ifstream file(argv[++i]);
        if (!file) {
            cerr << "Error opening file for player 1 links." << endl;
            return 1;
        }
        // Read links from file
        string linkType;
        while (file >> linkType) {
            p1LinkOrder.push_back(linkType);
        }
        link1Passed = true;
    } else if (string(argv[i]) == "-link2" && i + 1 < argc) {
        // Load links from custom file for player 2
        ifstream file(argv[++i]);
        if (!file) {
            cerr << "Error opening file for player 2 links." << endl;
            return 1;
        }
        // Read links from file
        string linkType;
        while (file >> linkType) {
            p2LinkOrder.push_back(linkType);
        }
        link2Passed = true;
    } else if (std::string(argv[i]) == "-graphics") {
      includeGraphics = true;
    }
  }

  random_device rd;
  mt19937 rng(rd());

  if (!link1Passed) {
    p1LinkOrder = {"V1", "V2", "V3", "V4", "D1", "D2", "D3", "D4"};
    shuffle(p1LinkOrder.begin(), p1LinkOrder.end(), rng);
  }
  if (!link2Passed) {
    p2LinkOrder = {"V1", "V2", "V3", "V4", "D1", "D2", "D3", "D4"};
    shuffle(p2LinkOrder.begin(), p2LinkOrder.end(), rng);
  }

  // configure abilities
  vector<unique_ptr<Ability>> p1Abilities;
  vector<unique_ptr<Ability>> p2Abilities;
  for (char a : p1AbilityOrder) {
    if (a == 'L') {
      p1Abilities.emplace_back(std::make_unique<LinkBoost>());
    }
    else if (a == 'F') {
      p1Abilities.emplace_back(std::make_unique<Firewall>());
    }
    else if (a == 'D') {
      p1Abilities.emplace_back(std::make_unique<Download>());
    }
    else if (a == 'P') {
      p1Abilities.emplace_back(std::make_unique<Polarize>());
    }
    else if (a == 'S') {
      p1Abilities.emplace_back(std::make_unique<Scan>());
    }
    else if (a == 'X') {
      p1Abilities.emplace_back(std::make_unique<SkipTurn>());
    }
    else if (a == 'B') {
      p1Abilities.emplace_back(std::make_unique<Buff>());
    }
    else if (a == 'T') {
      p1Abilities.emplace_back(std::make_unique<Teleport>());
    }
  }
  for (char a : p2AbilityOrder) {
    if (a == 'L') {
      p2Abilities.emplace_back(std::make_unique<LinkBoost>());
    }
    else if (a == 'F') {
      p2Abilities.emplace_back(std::make_unique<Firewall>());
    }
    else if (a == 'D') {
      p2Abilities.emplace_back(std::make_unique<Download>());
    }
    else if (a == 'P') {
      p2Abilities.emplace_back(std::make_unique<Polarize>());
    }
    else if (a == 'S') {
      p2Abilities.emplace_back(std::make_unique<Scan>());
    }
    else if (a == 'X') {
      p2Abilities.emplace_back(std::make_unique<SkipTurn>());
    }
    else if (a == 'B') {
      p2Abilities.emplace_back(std::make_unique<Buff>());
    }
    else if (a == 'T') {
      p2Abilities.emplace_back(std::make_unique<Teleport>());
    }
  }
  // p1 links
  std::vector<std::unique_ptr<Link>> p1Links;
  p1Links.emplace_back(Link::create(0, 0, p1LinkOrder[0][1] - '0', 1, p1LinkOrder[0][0] == 'V', 'a', 1, false));
  p1Links.emplace_back(Link::create(0, 1, p1LinkOrder[1][1] - '0', 1, p1LinkOrder[1][0] == 'V', 'b', 1, false));
  p1Links.emplace_back(Link::create(0, 2, p1LinkOrder[2][1] - '0', 1, p1LinkOrder[2][0] == 'V', 'c', 1, false));
  p1Links.emplace_back(Link::create(1, 3, p1LinkOrder[3][1] - '0', 1, p1LinkOrder[3][0] == 'V', 'd', 1, false));
  p1Links.emplace_back(Link::create(1, 4, p1LinkOrder[4][1] - '0', 1, p1LinkOrder[4][0] == 'V', 'e', 1, false));
  p1Links.emplace_back(Link::create(0, 5, p1LinkOrder[5][1] - '0', 1, p1LinkOrder[5][0] == 'V', 'f', 1, false));
  p1Links.emplace_back(Link::create(0, 6, p1LinkOrder[6][1] - '0', 1, p1LinkOrder[6][0] == 'V', 'g', 1, false));
  p1Links.emplace_back(Link::create(0, 7, p1LinkOrder[7][1] - '0', 1, p1LinkOrder[7][0] == 'V', 'h', 1, false));

  // p2 links
  std::vector<std::unique_ptr<Link>> p2Links;
  p2Links.emplace_back(Link::create(7, 0, p2LinkOrder[0][1] - '0', 1, p2LinkOrder[0][0] == 'V', 'A', 2, false));
  p2Links.emplace_back(Link::create(7, 1, p2LinkOrder[1][1] - '0', 1, p2LinkOrder[1][0] == 'V', 'B', 2, false));
  p2Links.emplace_back(Link::create(7, 2, p2LinkOrder[2][1] - '0', 1, p2LinkOrder[2][0] == 'V', 'C', 2, false));
  p2Links.emplace_back(Link::create(6, 3, p2LinkOrder[3][1] - '0', 1, p2LinkOrder[3][0] == 'V', 'D', 2, false));
  p2Links.emplace_back(Link::create(6, 4, p2LinkOrder[4][1] - '0', 1, p2LinkOrder[4][0] == 'V', 'E', 2, false));
  p2Links.emplace_back(Link::create(7, 5, p2LinkOrder[5][1] - '0', 1, p2LinkOrder[5][0] == 'V', 'F', 2, false));
  p2Links.emplace_back(Link::create(7, 6, p2LinkOrder[6][1] - '0', 1, p2LinkOrder[6][0] == 'V', 'G', 2, false));
  p2Links.emplace_back(Link::create(7, 7, p2LinkOrder[7][1] - '0', 1, p2LinkOrder[7][0] == 'V', 'H', 2, false));
  // create players
  auto player1 = Player::create(1, true, std::move(p1Abilities), std::move(p1Links), 0, 0);
  auto player2 = Player::create(2, false, std::move(p2Abilities), std::move(p2Links), 0, 0);
  Game game{std::move(player1), std::move(player2)};

  auto textObserver = std::make_unique<TextObserver>(true);
  game.attach(std::move(textObserver));
  if (includeGraphics) {
    std::unique_ptr<GraphicsObserver> p1Window = std::make_unique<GraphicsObserver>(&game, 1);  // P1 at top
    std::unique_ptr<GraphicsObserver> p2Window = std::make_unique<GraphicsObserver>(&game, 2);  // P2 at top;
    game.attach(std::move(p1Window));
    game.attach(std::move(p2Window));
  }
  game.notifyObservers(&game);

  string command;
  bool abilityUsed = false;
  while (cin >> command)
  {
    if (command == "ability")
    {
      if (abilityUsed) {
        cout << "Ability already used this turn" << endl;
        continue;
      }
      int ability;
      cin >> ability;
      bool result = game.useAbility(ability, game.whosTurn());
      if (!result) {
        cout << "Ability failed" << endl;
      } else {
        abilityUsed = true;
      }
    }
    else if (command == "move")
    {
      char id;
      char dir;
      cin >> id >> dir;
      Link *toMove = game.getLinkFromID(id, game.whosTurn());
      if (toMove && !toMove->getIsDownloaded())
      {
        game.moveLink(toMove, dir);
      }
      abilityUsed = false;
      if (game.checkWon()) {
        game.clearObservers();
        break;
      }
    }
    else if (command == "abilities")
    {
      game.displayAbilities(game.getPlayer(game.whosTurn() - 1).get());
    }
    else if (command == "board")
    {
      game.notifyObservers(&game);
    }
    else if (command == "quit")
    {
      game.clearObservers();
      return 0;
    }
    else if (command == "sequence") 
    {
      string filename;
      cin >> filename;
      
      ifstream commandFile(filename);
      if (!commandFile) {
        cout << "Error: Could not open file " << filename << endl;
        continue;
      }

      string fileCommand;
      string line;
      while (getline(commandFile, line)) {
        istringstream iss(line);
        iss >> fileCommand;
        
        if (fileCommand == "ability") {
          if (abilityUsed) {
            cout << "Ability already used this turn" << endl;
            continue;
          }
          int ability;
          iss >> ability;
          string remaining;
          getline(iss, remaining);
          stringstream temp(remaining);
          auto cinbuf = cin.rdbuf(temp.rdbuf());
          bool result = game.useAbility(ability, game.whosTurn());
          cin.rdbuf(cinbuf);
          
          if (!result) {
              cout << "Ability failed" << endl;
          } else {
              abilityUsed = true;
          }
        }
        else if (fileCommand == "move") {
          char id, dir;
          iss >> id >> dir;
          Link *toMove = game.getLinkFromID(id, game.whosTurn());
          if (toMove && !toMove->getIsDownloaded()) {
            game.moveLink(toMove, dir);
          }
          abilityUsed = false;
          if (game.checkWon()) {
            game.clearObservers();
            break;
          }
        }
        else if (fileCommand == "abilities") {
            game.displayAbilities(game.getPlayer(game.whosTurn() - 1).get());
        }
        else if (fileCommand == "board") {
            game.notifyObservers(&game);
        }
        else if (fileCommand == "quit") {
            game.clearObservers();
            commandFile.close();
            return 0;
        }
      }
      commandFile.close();
    }
  }
  return 0;
}
