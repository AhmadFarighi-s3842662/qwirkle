#include "Board.h"
#include "TileCodes.h"

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

Tile* Board::tileAt(char row, int col) {
    return nullptr;
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