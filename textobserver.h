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
    void updateDownloaded(int playerID);
    void updateAbilityCounter(int playerID);
    void printOwnedLinks(int playerID);
    void updateKnownLinks(int playerID); // pass in the playerID that has the current turn
    void updateCellTextDisplay(std::unique_ptr<Cell> c);

public:
    TextObserver(bool twoPlayers);
    void notify(Subject &game) override;
};

#endif