#include "graphicsobserver.h"

GraphicsObserver::GraphicsObserver(Subject *sub, int width, int height)
    : subject{sub}, width{width}, height{height} {
        window = std::make_unique<Xwindow>(width, height);
        previous.resize(8, std::vector<char>(8, '.'));
        drawFullBoard();
}

GraphicsObserver::~GraphicsObserver() {
    subject->detach(this);
}

void GraphicsObserver::drawFullBoard() {
    int boardSize = 8;
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            int colour = ((i + j) % 2 == 0) ? Xwindow::LightGray : Xwindow::DarkGray;
            drawCell(i, j, colour, subject->charAt(i, j));
            previous[i][j] = subject->charAt(i, j);
        }
    }
}

void GraphicsObserver::drawCell(int i, int j, int colour, char piece) {
    int squareWidth = width / 8;
    int squareHeight = height / 8;
    int x = j * squareWidth;
    int y = i * squareHeight;
    
    window->fillRectangle(x, y, squareWidth, squareHeight, colour);
    
    if (piece != '.') {
        window->drawString(
            x + squareWidth/3,
            y + squareHeight/2 + 5,
            std::string(1, piece)
        );
    }
}

void GraphicsObserver::notify(Subject &subject) {
    int boardSize = 8;
    
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            char currentPiece = subject.charAt(i, j);
            if (currentPiece != previous[i][j]) {
                int colour = ((i + j) % 2 == 0) ? Xwindow::LightGray : Xwindow::DarkGray;
                drawCell(i, j, colour, currentPiece);
                previous[i][j] = currentPiece;
            }
        }
    }
}