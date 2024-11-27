#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"
#include <memory>
#include "cell.h"

class TextObserver : public Observer
{
    bool twoPlayers;
    const int LENGTH = 8;
    const int WIDTH = 8;
private:
    void updateDownloaded(Player& player);
    void updateAbilityCounter(Player& player);
    void printOwnedLinks(Player& player);
    void updateKnownLinks(Player& player); // pass in the player that has the current turn
    void updateCellTextDisplay(Player& player);

public:
    TextObserver(bool twoPlayers);
    void notify(Subject &subject) override;
};

#endif