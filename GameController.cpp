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
}