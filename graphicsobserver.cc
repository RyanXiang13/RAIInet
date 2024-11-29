#include "graphicsobserver.h"
#include "link.h"

GraphicsObserver::GraphicsObserver(Subject *sub, int startingPlayer)
    : subject{sub}, topPlayer{startingPlayer} {
        window = std::make_unique<Xwindow>(WIDTH, HEIGHT);
        previous.resize(8, std::vector<char>(8, '.'));
        initialize();
}

GraphicsObserver::~GraphicsObserver() {
    subject->detach(this);
}

void GraphicsObserver::displayWelcome() {
    // hi
}

void GraphicsObserver::initialize() {    
    // top abilities
    window->fillRectangle(0, 0, WIDTH, ABILITY_HEIGHT, Xwindow::Slate);
    displayAbilities(*subject->getPlayer(topPlayer - 1));
    
    // board
    drawFullBoard();
    
    // bottom abilities
    window->fillRectangle(0, HEIGHT - ABILITY_HEIGHT, WIDTH, ABILITY_HEIGHT, Xwindow::Slate);
    int bottomPlayer = (topPlayer == 1) ? 2 : 1;
    displayAbilities(*subject->getPlayer(bottomPlayer - 1));
}

void GraphicsObserver::drawFullBoard() {
    for (int i = 0; i < SQUARES; ++i) {
        for (int j = 0; j < SQUARES; ++j) {
            char piece = subject->charAt(i, j);
            int colour = ((i + j) % 2 == 0) ? Xwindow::LightGray : Xwindow::DarkGray;
            
            // checks if firewall
            if (piece == 'w' || piece == 'm') {
                colour = Xwindow::Orange;
            } else if (piece != '.') {
                bool isPieceFound = false; // default unless the following search finds the piece
                
                const auto& topPlayerLinks = subject->getPlayer(topPlayer - 1)->getOwnedLinks();
                for (const auto& link : topPlayerLinks) {
                    if (link->getID() == piece) {
                        colour = link->getIsVirus() ? Xwindow::Red : Xwindow::Green;
                        isPieceFound = true;
                        break;
                    }
                }
                
                if (!isPieceFound) {
                    int bottomPlayer = (topPlayer == 1) ? 2 : 1;
                    const auto& bottomPlayerLinks = subject->getPlayer(bottomPlayer - 1)->getOwnedLinks();
                    for (const auto& link : bottomPlayerLinks) {
                        if (link->getID() == piece) {
                            if (!link->getIsFound()) {
                                colour = Xwindow::Ivory;
                            }
                            break;
                        }
                    }
                }
            }
            
            drawCell(i, j, colour, piece);
            previous[i][j] = piece;
        }
    }
}

void GraphicsObserver::notify(Subject &subject) {  
    for (int i = 0; i < SQUARES; ++i) {
        for (int j = 0; j < SQUARES; ++j) {
            char currentPiece = subject.charAt(i, j);
            bool shouldRedraw = (currentPiece != previous[i][j]);
            int colour = ((i + j) % 2 == 0) ? Xwindow::LightGray : Xwindow::DarkGray;
            
            if (currentPiece == 'w' || currentPiece == 'm') {
                colour = Xwindow::Orange;
            } else if (currentPiece != '.') {
                bool isPieceFound = false;
                
                const auto& topPlayerLinks = subject.getPlayer(topPlayer - 1)->getOwnedLinks();
                for (const auto& link : topPlayerLinks) {
                    if (link->getID() == currentPiece) {
                        colour = link->getIsVirus() ? Xwindow::Red : Xwindow::Green;
                        isPieceFound = true;
                        break;
                    }
                }
                
                if (!isPieceFound) {
                    int bottomPlayer = (topPlayer == 1) ? 2 : 1;
                    const auto& bottomPlayerLinks = subject.getPlayer(bottomPlayer - 1)->getOwnedLinks();
                    for (const auto& link : bottomPlayerLinks) {
                        if (link->getID() == currentPiece) {
                            if (link->getIsFound()) {
                                colour = link->getIsVirus() ? Xwindow::Red : Xwindow::Green;
                                shouldRedraw = true;
                            } else {
                                colour = Xwindow::Ivory;
                            }
                            break;
                        }
                    }
                }
            }
            
            if (shouldRedraw) {
                drawCell(i, j, colour, currentPiece);
                previous[i][j] = currentPiece;
            }
        }
    }
    
    int bottomPlayer = (topPlayer == 1) ? 2 : 1;
    displayAbilities(*subject.getPlayer(topPlayer - 1));
    displayAbilities(*subject.getPlayer(bottomPlayer - 1));
}

void GraphicsObserver::drawCell(int i, int j, int colour, char piece) {
    int squareWidth = WIDTH / SQUARES;
    int squareHeight = WIDTH / SQUARES;
    int x = j * squareWidth;
    int y = i * squareHeight + ABILITY_HEIGHT;
    
    window->fillRectangle(x, y, squareWidth, squareHeight, colour);
    
    if (piece != '.') {
        window->drawString(
            x + squareWidth/3,
            y + squareHeight/2 + 5,
            std::string(1, piece)
        );
    }
}

void GraphicsObserver::displayAbilities(Player &player) {
    bool isTopPlayer = (player.getPlayerID() == topPlayer);
    int baseY = isTopPlayer ? 10 : 512;  
    
    window->fillRectangle(0, isTopPlayer ? 0 : HEIGHT - ABILITY_HEIGHT, 
                         WIDTH, ABILITY_HEIGHT, Xwindow::Slate);
    
    window->drawString(2, baseY, "Player " + std::to_string(player.getPlayerID()) + ":");
    window->drawString(2, baseY + 10, 
        "Downloaded: " + std::to_string(player.getNumOfData()) + "D, " + 
        std::to_string(player.getNumOfVirus()) + "V");
    window->drawString(2, baseY + 20, "Abilities: " + std::to_string(player.getAbilityCount()));
    
    const auto& ownedLinks = player.getOwnedLinks();
    int woffset = 0;
    int hoffset = 0;
    for (const auto& link : ownedLinks) {
        if (woffset % 200 == 0) {
            hoffset += 10;
            woffset = 0;
        }

        std::string output;
        if (isTopPlayer || link->getIsFound()) {
            output = std::string(1, link->getID()) + ": " + link->getName();
            window->drawString(2 + woffset, baseY + 30 + hoffset, output);
        } else {
            output = std::string(1, link->getID()) + ": ?";
            window->drawString(2 + woffset, baseY + 30 + hoffset, output);
        }
        woffset += 50;
    }
}

void GraphicsObserver::displayWin(int winner) {

}
