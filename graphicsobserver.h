#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H
#include "observer.h"
#include "window.h"
#include "cell.h"
#include "subject.h"
#include "ability.h"
#include "textobserver.h"
#include "link.h"
#include <memory>
#include <vector>
#include <string>

const int WIDTH = 400;
const int HEIGHT = 600;
const int ABILITY_HEIGHT = 100;
const int BOARD_HEIGHT = 400;
const int SQUARES = 8;

class GraphicsObserver : public Observer
{
private:
    Subject* subject;
    const int topPlayer;
    std::unique_ptr<Xwindow> window;
    std::vector<std::vector<char>> previous;

    void displayWin(int winner) override;
    void displayWelcome() override;
    void initialize();
    
    void drawFullBoard();
    void drawCell(int i, int j, int colour, char piece);
    
    void updateDownloadedDisplay();
    void updateAbilityCounterDisplay();
    void updateKnownLinksDisplay(int playerID);
    void updateCellDisplay(std::unique_ptr<Cell> c);
    void displayAbilities(Player &player) override;

public:
    GraphicsObserver(Subject *sub, int startingPlayer);
    ~GraphicsObserver();
    void notify(Subject &subject) override;
};

#endif
