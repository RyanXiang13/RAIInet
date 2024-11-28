#include "graphicsobserver.h"

GraphicsObserver::GraphicsObserver(Subject *sub, int width, int height)
    : subject{sub}, width{width}, height{height} {
        window = new Xwindow(width, height);
        subject->attach(this);
    }

GraphicsObserver::~GraphicsObserver() {
    subject->detach(this);
    delete window;
}

void GraphicsObserver::notify() {
    int boardSize = 8;
    int squareWidth = width / boardSize;
    int squareHeight = height / boardSize;
    for (int i = top i <= bottom; ++i) {
        for (int j = left; j <= right; ++j) {
            int colour = ((i + j) % 2 == 0) ? Xwindow::White : Xwindow::Black;
            int x = j * squareWidth;
            int y = i * squareHeight;
            window->fillRectangle(x, y, squareWidth, squareHeight, colour);
        }
    }
}