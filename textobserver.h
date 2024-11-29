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
    void updateDownloaded(Player& player); // DONE
    void updateAbilityCounter(Player& player); // DONE
    void printOwnedLinks(Player& player); // DONE
    void updateKnownLinks(Player& player); // pass in player who's turn it ISN'T // DONE

public:
    TextObserver(bool twoPlayers);
    void notify(Subject &subject) override;
    void displayAbilities(Player& player) override;
    void displayWin(int winner);
};

#endif
