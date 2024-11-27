#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"
#include <memory>
#include "cell.h"

class TextObserver : public Observer
{
    int top, bottom, left, right;
private:
    void updateDownloadedTextDisplay(int playerID);
    void updateAbilityCounterTextDisplay(int playerID);
    void updateKnownLinksTextDisplay(int playerID); // pass in the playerID that has the current turn
    void updateCellTextDisplay(std::unique_ptr<Cell> c);

public:
    TextObserver(bool twoPlayers);
    void notify(Subject &game) override;
};

#endif