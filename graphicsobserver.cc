#include "graphicsobserver.h"

GraphicsObserver::GraphicsObserver(Subject *sub, int width, int height)
    : subject{sub}, width{width}, height{height} {
        window = std::make_unique<Xwindow>(width, height);
}

std::unique_ptr<GraphicsObserver> GraphicsObserver::create(Subject* sub, int width, int height) {
    auto observer = std::unique_ptr<GraphicsObserver>(new GraphicsObserver(sub, width, height));
    sub->attach(std::unique_ptr<Observer>(observer.release()));
    return observer;
}

GraphicsObserver::~GraphicsObserver() {
    subject->detach(this);
}

void GraphicsObserver::notify(Subject &subject) {    
    int boardSize = 8;
    int squareWidth = width / boardSize;
    int squareHeight = height / boardSize;    
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            int colour = ((i + j) % 2 == 0) ? Xwindow::White : Xwindow::Black;
            int x = j * squareWidth;
            int y = i * squareHeight;
            
            window->fillRectangle(x, y, squareWidth, squareHeight, colour);
            
            char piece = subject.charAt(i, j);
            if (piece != '.') {
                std::string pieceStr(1, piece);
                window->drawString(
                    x + squareWidth/3,  
                    y + squareHeight/2 + 5, 
                    pieceStr
                );
            }
        }
    }
}
