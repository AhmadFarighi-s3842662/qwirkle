#include <cctype>

#include "Board.h"
#include "TileCodes.h"

#define ASCII_VALUE_A 65

Board::Board() {
    // Initialise board with rows of "blank" tiles to represent empty spaces
    for (int i = 0; i < BOARD_MAX_DIM; ++i) {
        std::vector<Tile*> tileRow;

        for (int j = 0; j < BOARD_MAX_DIM; ++j) {
            // Tiles have a move constructor, so there are no memory leaks here
            tileRow.push_back(new Tile(NO_COLOUR, NO_SHAPE));
        }

        board.push_back(tileRow);
    }
}

Board::Board(Board& other) {
    // Make copies of all tiles in the source board
    for (unsigned int i = 0; i < other.board.size(); ++i) {
        std::vector<Tile*> tileRow;

        for (unsigned int j = 0; j < other.board.at(i).size(); ++j) {
            Tile* currentTile = other.board.at(i).at(j);
            tileRow.push_back(new Tile(*currentTile));
        }

        board.push_back(tileRow);
    }
}

Board::~Board() {
    for (unsigned int i = 0; i < board.size(); ++i) {
        for (unsigned int j = 0; j < board.at(i).size(); ++j) {
            delete board.at(i).at(j);
        }
    }
}

int Board::getHeight() {
    return (int) board.size();
}

int Board::getWidth() {
    // Gets the length of the first row, which, in normal operation, should
    // have a length equal to that of all other rows.
    return (int) board.at(0).size();
}

Tile* Board::tileAt(char row, int col) {
    Tile* returnPointer = nullptr;
    Tile* boardPos = board.at(rowCharToIndex(row)).at(col);

    if (!boardPos->hasBlankValue()) {
        returnPointer = new Tile(*boardPos);
    }

    return returnPointer;
}

bool Board::placeTile(Tile tile, char row, int col) {
    return false;
}

std::string Board::toString() {
    return "";
}

std::string Board::serialise() {
    return "";
}

int Board::rowCharToIndex(char row) {
    row = std::toupper(row);

    /*
     * ASCII uppercase characters begin from 65, so subtracting 65 from the
     * character's value produces the corresponding row index in the vector.
     * 
     * A useful table can be found here:
     * https://www.w3schools.com/charsets/ref_html_ascii.asp
     */ 
    return (int) row - ASCII_VALUE_A;
}