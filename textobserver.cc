#include <iostream>
#include "textobserver.h"
#include "game.h"

TextObserver::TextObserver(bool twoPlayers) : twoPlayers{twoPlayers} {}

void TextObserver:notify(Subject &game) 