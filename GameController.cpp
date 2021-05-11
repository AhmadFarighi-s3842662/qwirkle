#include "GameController.h"

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::istringstream;

GameController::GameController(int playerCount)
{
    this->game = new Game(playerCount);
    this->pCount = playerCount;
    for (int i = 0;i<pCount;i++){
        addPlayer();
    }
}

GameController::~GameController()
{
    if (game != nullptr)
    {
        delete game;
    }
}

void GameController::addPlayer() {
   string input = "";
   cout << "Player "<<game->getPlayerCount()+1<<" name: " << endl;;
   cout << "> ";
   cin >> input;
   game->addPlayer(new Player(input));
}

void GameController::gameStart(){
    game->dealPlayerTiles();
    game->setCurrentPlayer(game->getPlayer(0));
}

void GameController::gameLoop(){
    // Print current state of the board
    cout << game->getBoard()->toString() << endl;

    // Ask current player for thier move
    askForPlayerMove();

    // perform move if valid, if not step back

    // check game status

    // switch current player
    if (game->getCurrentPlayer() == game->getPlayer(0))
    {
        game->setCurrentPlayer(game->getPlayer(1));
    }
    else {
        game->setCurrentPlayer(game->getPlayer(0));
    }
}

string GameController::askForPlayerMove(){
    cout << "Current player: " << game->getCurrentPlayer()->getName() << endl
         << "Player's hand: " << game->getCurrentPlayer()->getHand()->toString() << endl;
    string input = "";
    cout << "Move format \"<TILE> to <LOCATION>\" Example: R0 to A1" << endl;;
    cout << "> ";
    cin >> input;
    return input;
}

void GameController::validateMoveInput(string input){
    //uuuuuuuggggggghhhhhhhhhhhhhh
}

void GameController::makeAMove(string tileSTR, string moveSTR){

    string tile = tileSTR;
    game->getCurrentPlayer()->removeFromHand(tile);

    string bodge = "" + moveSTR.at(1);
    int col = std::stoi (bodge);

    Tile* mTile = new Tile(tileSTR.at(0), tileSTR.at(1));
    game->getBoard()->placeTile(*mTile,
                                moveSTR.at(0),
                                col);
}