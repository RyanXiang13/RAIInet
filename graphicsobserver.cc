#include "graphicsobserver.h"

GraphicsObserver::GraphicsObserver(Subject *sub, int width, int height, int abilityHeight, int boardHeight, int squares)
    : subject{sub}, width{width}, height{height}, abilityHeight{abilityHeight}, boardHeight{boardHeight}, squares{squares} {
        window = std::make_unique<Xwindow>(width, height);
        previous.resize(8, std::vector<char>(8, '.'));
        initialize();
}

GraphicsObserver::~GraphicsObserver() {
    subject->detach(this);
}

void GraphicsObserver::welcomeScreen(int type) {
    if (type == 0) {
        // welcome
    } else if (type == 1) {
        // goodbye
    } 
}

void GraphicsObserver::initialize() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // abilities p1
            if (i < abilityHeight) {
                window->fillRectangle(0, 0, width, abilityHeight, Xwindow::Slate);
                window->drawString(width/squares, width/squares, "Player 1");
                i += abilityHeight;
            } else if (i < height - abilityHeight) { // links (the board)
                drawFullBoard();
            } else { // abilities p2
                window->fillRectangle(0, height - abilityHeight, width, abilityHeight, Xwindow::Slate);
            }
        }
    }
}

void GraphicsObserver::drawFullBoard() {
    for (int i = 0; i < squares; ++i) {
        for (int j = 0; j < squares; ++j) {
            int colour = ((i + j) % 2 == 0) ? Xwindow::LightGray : Xwindow::DarkGray;
            drawCell(i, j, colour, subject->charAt(i, j));
            previous[i][j] = subject->charAt(i, j);
        }
    }
}

// change the addition of "abilityHeight" to drawFullBoard and notify function instead
 void GraphicsObserver::drawCell(int i, int j, int colour, char piece) {
    int squareWidth = width / squares;
    int squareHeight = width / squares;
    int x = j * squareWidth;
    int y = i * squareHeight + abilityHeight;
    
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
    // need to update to work with abilities AND links  
    for (int i = 0; i < squares; ++i) {
        for (int j = 0; j < squares; ++j) {
            char currentPiece = subject.charAt(i, j);
            if (currentPiece != previous[i][j]) {
                int colour = ((i + j) % 2 == 0) ? Xwindow::LightGray : Xwindow::DarkGray;
                drawCell(i, j, colour, currentPiece);
                previous[i][j] = currentPiece;
            }
        }
    }
}

// aka drawAbility
void GraphicsObserver::displayAbilities(Player &player) {
    //p1 abilities
    

    //p2 abilities
}
