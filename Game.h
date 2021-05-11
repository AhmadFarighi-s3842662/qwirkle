#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include "Board.h"
#include "LinkedList.h"
#include "Player.h"
#include "TileCodes.h"

class Game
{
private:
    Board* board;
    LinkedList* tileBag;
    Player** players;
    int pCount;

    Player* currentPlayer;
    int rowCharToIndex(char row);

public:
    Game(int playerCount);
    Game(Game& other);
    ~Game();

    bool placeTile();
    bool placeTile(Tile& tile, char row, int col);
    bool replaceTile();
    bool Game::validateTilesInDirection(Tile& tile, int originX, int originY, int moveX, int moveY);
    bool saveGame;

    int getPlayerCount();
    void dealPlayerTiles();
    void addPlayer(Player* newPlayer);
    void printGame();
    Player* getPlayer(int i);
    Player* getCurrentPlayer();
    void setCurrentPlayer(Player* playa);

    Board* getBoard();
    LinkedList* getTileBag();
};

#endif // ASSIGN2_GAME_H