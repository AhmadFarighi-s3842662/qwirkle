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

public:
    Game(int playerCount);
    Game(Game& other);
    ~Game();

    bool placeTile();
    bool replaceTile();
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