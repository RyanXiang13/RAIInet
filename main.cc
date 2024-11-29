#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include "game.h"
#include "player.h"
#include "link.h"
#include "ability.h"
#include "textobserver.h"
#include "graphicsobserver.h"
#include "download.h"
#include "scan.h"
#include "firewall.h"
#include "polarize.h"
#include "linkboost.h"
#include "teleport.h"
#include "skipturn.h"

using namespace std;

int main()
{
  // p1 links
  std::vector<std::unique_ptr<Link>> p1Links;
  p1Links.push_back(Link::create(0, 0, 1, 1, false, 'a', 1, false));
  p1Links.push_back(Link::create(0, 1, 2, 1, false, 'b', 1, false));
  p1Links.push_back(Link::create(0, 2, 3, 1, false, 'c', 1, false));
  p1Links.push_back(Link::create(1, 3, 4, 1, false, 'd', 1, false));
  p1Links.push_back(Link::create(1, 4, 1, 1, true, 'e', 1, false));
  p1Links.push_back(Link::create(0, 5, 2, 1, true, 'f', 1, false));
  p1Links.push_back(Link::create(0, 6, 3, 1, true, 'g', 1, false));
  p1Links.push_back(Link::create(0, 7, 4, 1, true, 'h', 1, false));

  // p2 links
  std::vector<std::unique_ptr<Link>> p2Links;
  p2Links.push_back(Link::create(7, 0, 1, 1, false, 'A', 2, false));
  p2Links.push_back(Link::create(7, 1, 2, 1, false, 'B', 2, false));
  p2Links.push_back(Link::create(7, 2, 3, 1, false, 'C', 2, false));
  p2Links.push_back(Link::create(6, 3, 4, 1, false, 'D', 2, false));
  p2Links.push_back(Link::create(6, 4, 1, 1, true, 'E', 2, false));
  p2Links.push_back(Link::create(7, 5, 2, 1, true, 'F', 2, false));
  p2Links.push_back(Link::create(7, 6, 3, 1, true, 'G', 2, false));
  p2Links.push_back(Link::create(7, 7, 4, 1, true, 'H', 2, false));

  // Create players
  std::vector<std::unique_ptr<Ability>> p1Abilities;
  p1Abilities.emplace_back(std::make_unique<Teleport>());
  p1Abilities.emplace_back(std::make_unique<LinkBoost>());
  p1Abilities.emplace_back(std::make_unique<LinkBoost>());
  p1Abilities.emplace_back(std::make_unique<Download>());
  p1Abilities.emplace_back(std::make_unique<Scan>());

  std::vector<std::unique_ptr<Ability>> p2Abilities;
  p2Abilities.emplace_back(std::make_unique<Firewall>());
  p2Abilities.emplace_back(std::make_unique<Firewall>());
  p2Abilities.emplace_back(std::make_unique<Scan>());
  p2Abilities.emplace_back(std::make_unique<Polarize>());
  p2Abilities.emplace_back(std::make_unique<Download>());

  auto player1 = Player::create(1, true, std::move(p1Abilities), std::move(p1Links));
  auto player2 = Player::create(2, false, std::move(p2Abilities), std::move(p2Links));
  Game game{std::move(player1), std::move(player2)};

  auto textObserver = std::make_unique<TextObserver>(true);
  game.attach(std::move(textObserver));
  // top 400x100 for p1, bottom 400x100 for p2
  // game is 400x400
  auto graphicsObserver = std::make_unique<GraphicsObserver>(&game, 400, 600, 100, 400, 8);
  game.attach(std::move(graphicsObserver));
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
    else if (command == "sequence")
    {
      continue;
    }
    else if (command == "quit")
    {
      game.clearObservers();
      break;
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
