#include <iostream>
#include <memory>
#include <vector>
#include "game.h"
#include "player.h"
#include "link.h"
#include "textobserver.h"
using namespace std;

int main() {
    //p1 links
    std::vector<std::unique_ptr<Link>> p1Links;
    p1Links.push_back(Link::create(0, 0, 1, 1, false, 'a', 1, false));
    p1Links.push_back(Link::create(0, 1, 2, 1, false, 'b', 1, false));
    p1Links.push_back(Link::create(0, 2, 3, 1, false, 'c', 1, false));
    p1Links.push_back(Link::create(1, 3, 4, 1, false, 'd', 1, false));
    p1Links.push_back(Link::create(1, 4, 1, 1, true, 'e', 1, false));
    p1Links.push_back(Link::create(0, 5, 2, 1, true, 'f', 1, false));
    p1Links.push_back(Link::create(0, 6, 3, 1, true, 'g', 1, false));
    p1Links.push_back(Link::create(0, 7, 4, 1, true, 'h', 1, false));
    cout << p1Links[0]->getCol() << endl;

    // p2 links
    std::vector<std::unique_ptr<Link>> p2Links;
    p2Links.push_back(Link::create(7, 0, 1, 1, false, 'A', 1, false));
    p2Links.push_back(Link::create(7, 1, 2, 1, false, 'B', 1, false));
    p2Links.push_back(Link::create(7, 2, 3, 1, false, 'C', 1, false));
    p2Links.push_back(Link::create(6, 3, 4, 1, false, 'D', 1, false));
    p2Links.push_back(Link::create(6, 4, 1, 1, true, 'E', 1, false));
    p2Links.push_back(Link::create(7, 5, 2, 1, true, 'F', 1, false));
    p2Links.push_back(Link::create(7, 6, 3, 1, true, 'G', 1, false));
    p2Links.push_back(Link::create(7, 7, 4, 1, true, 'H', 1, false));
    

    // Create players
    auto player1 = Player::create(1, true, std::vector<int>(9, 2), std::move(p1Links));
    auto player2 = Player::create(2, false, std::vector<int>(9, 2), std::move(p2Links));
    cout << player2->getPlayerID() << endl;
    cout << player2->getOwnedLinks()[6]->getID() << endl;
    // Create game
    Game game{std::move(player1), std::move(player2)};
  
    // Create and attach observer
    auto observer = std::make_unique<TextObserver>(true);
    game.attach(std::move(observer));
    
    // Display initial state
    game.notifyObservers(&game);

    return 0;
}