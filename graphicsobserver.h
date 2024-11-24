#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H
#include "observer.h"
#include "window.h"
#include "cell.h"
#include "subject.h"
#include <memory>

class GraphicsObserver : public Observer
{
private:
    std::unique_ptr<Xwindow> window;
    int width;
    int height;
    void updateDownloadedDisplay();
    void updateAbilityCounterDisplay();
    void updateKnownLinksDisplay(int playerID); // pass in the playerID that has the current turn
    void updateCellDisplay(std::unique_ptr<Cell> c);

public:
    GraphicsObserver(int width, int height);
    void notify(Subject &game) override;
};

#endif