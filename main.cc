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
    
    return 0;
}