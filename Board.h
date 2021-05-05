#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <string>
#include <vector>

#include "Tile.h"

// Maximum board size for Milestone 2 is 26x26
#define BOARD_MAX_DIM 26

class Board {
public:
    // Constructors/Destructor
    Board();
    Board(Board& other);
    ~Board();

    // Get a pointer to the tile at a position on the board, or a nullptr if
    // there is no tile at that position
    Tile* tileAt(char row, int col);

    // Place a tile on the board. Return true if successful, otherwise false
    // Stores a copy of the given tile in the board.
    bool placeTile(Tile tile, char row, int col);

    // Get the board in string format, for printing to the console
    std::string toString();

    // Get the board in string format, for writing to a game save file
    std::string serialise();

private:
    std::vector<std::vector<Tile>> board;
};

#endif // ASSIGN2_BOARD_H