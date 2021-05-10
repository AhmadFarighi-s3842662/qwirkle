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
    cout << game->getBoard()->toString() << endl;
    askForPlayerMove();
    // Print current state of the board
    // Ask current player for thier move
    // perform move if valid, if not step back
    // check game status

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
