#ifndef ASSIGN2_GAMECONTROLLER_H
#define ASSIGN2_GAMECONTROLLER_H

#include "Game.h"

class GameController
{
private:
    Game* game;
public:
    GameController(/* args */);
    ~GameController();

    string addPlayer(int x);
    void gameStart();

};

#endif // ASSIGN2_NODE_H