#ifndef ASSIGN2_GAMECONTROLLER_H
#define ASSIGN2_GAMECONTROLLER_H

#include "Game.h"

class GameController
{
private:
    Game* game;
    int pCount;
public:
    GameController(int playerCount);
    GameController(Player* p1, Player* p2, Board& board, LinkedList& tileBag,
                   int currentPlayerNo);
    ~GameController();

    void addPlayer();
    void gameStart();
    void gameLoop();

    string askForPlayerMove();
    void validateMoveInput(string input);

    void makeAMove(string tileSTR, string moveSTR);
    void replaceATile(string tileSTR);

    bool validate_Place(string input);
    bool validate_Replace(string input);
    bool validate_save(std::vector<std::string>& input);

};

#endif // ASSIGN2_NODE_H