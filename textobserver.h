#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"
#include <memory>
#include "cell.h"

class TextObserver : public Observer
{
private:
    void updateDownloadedTextDisplay();
    void updateAbilityCounterTextDisplay();
    void updateKnownLinksTextDisplay(int playerID); // pass in the playerID that has the current turn
    void updateCellTextDisplay(std::unique_ptr<Cell> c);

public:
    TextObserver();
    void notify(Subject &game) override;
};

#endif