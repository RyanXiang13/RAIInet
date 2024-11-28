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
    p1Links.push_back(Link::create(0, 1, 2, 1, true, 'b', 1, false));
    cout << p1Links[0]->getCol();
    // p2 links
    std::vector<std::unique_ptr<Link>> p2Links;
    p2Links.push_back(Link::create(7, 0, 1, 1, false, 'y', 2, false));
    p2Links.push_back(Link::create(7, 1, 2, 1, true, 'z', 2, false));
    
    // Create players
    auto player1 = Player::create(1, true, std::vector<int>(9, 2), std::move(p1Links));
    auto player2 = Player::create(2, false, std::vector<int>(9, 2), std::move(p2Links));
    
    // Create game
    auto game = std::make_unique<Game>(std::move(player1), std::move(player2));
    
    // Create and attach observer
    auto observer = std::make_unique<TextObserver>(true);
    game->attach(std::move(observer));
    
    // Display initial state
    game->notifyObservers(game.get());
    
    return 0;
}