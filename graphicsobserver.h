#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H
#include "observer.h"
#include "window.h"
#include "cell.h"
#include "subject.h"
#include <memory>
#include <vector>

class GraphicsObserver : public Observer
{
private:
    Subject* subject;
    std::unique_ptr<Xwindow> window;
    int width;
    int height;
    std::vector<std::vector<char>> previous;
    
    void drawFullBoard();
    void drawCell(int i, int j, int colour, char piece);
    
    void updateDownloadedDisplay();
    void updateAbilityCounterDisplay();
    void updateKnownLinksDisplay(int playerID);
    void updateCellDisplay(std::unique_ptr<Cell> c);

public:
    GraphicsObserver(Subject *sub, int width, int height);
    ~GraphicsObserver();
    void notify(Subject &subject) override;
};

#endif