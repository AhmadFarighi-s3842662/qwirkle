#ifndef ASSIGN2_GAMECONTROLLER_H
#define ASSIGN2_GAMECONTROLLER_H

#include "Game.h"

class GameController
{
private:
    Game* game;
    int pCount;
    bool keepGoing;
public:
    GameController(int playerCount);
    ~GameController();

    void addPlayer();
    void gameStart();
    void gameLoop();

    string askForPlayerMove();
    bool validateMoveInput(string input);

    bool makeAMove(string tileSTR, string moveSTR);
    bool replaceATile(string tileSTR);

    bool validate_Place(string input);
    bool validate_Replace(string input);
    bool validate_save(std::vector<std::string>& input);

};

#endif // ASSIGN2_NODE_H