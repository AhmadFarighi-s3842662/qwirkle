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
    Player* player1;
    Player* player2;

    Player* currentPlayer;

public:
    Game(string p1, string p2);
    Game(Game& other);
    ~Game();

    bool placeTile();
    bool replaceTile();
    bool saveGame;

};

#endif // ASSIGN2_GAME_H