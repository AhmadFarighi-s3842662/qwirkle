#include "GameController.h"

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::istringstream;

GameController::GameController()
{
    // Starts with a nullptr, as it needs to get the player names input.
    game = nullptr;
}

GameController::~GameController()
{
    if (game != nullptr)
    {
        delete game;
    }
}

string GameController::addPlayer(int x) {
   string input = "";
   cout << "Player "<<x<<" name: " << endl;;
   cout << "> ";
   cin >> input;
   return input;
}

void GameController::gameStart(){
    string p1 = addPlayer(1);
    string p2 = addPlayer(2);
    game = new Game(p1,p2);
    game->setCurrentPlayer(game->getPlayer1());
}

void GameController::gameLoop(){
    // Print current state of the board
    cout << game->getBoard()->toString() << endl;

    // Ask current player for thier move
    askForPlayerMove();

    // perform move if valid, if not step back

    // check game status

    // switch current player
    if (game->getCurrentPlayer() == game->getPlayer1())
    {
        game->setCurrentPlayer(game->getPlayer2());
    }
    else {
        game->setCurrentPlayer(game->getPlayer1());
    }
}

string GameController::askForPlayerMove(){
    cout << "Current player: " << game->getCurrentPlayer()->getName() << endl
         << "Player's hand: " << game->getCurrentPlayer()->getHand() << endl;
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