#include "GameController.h"

#include <iostream>
#include <string>
#include <regex>

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
    // This block borrowed and modified from: 
    // https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
    std::istringstream iss(input);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());

    //DEBUG PRINTS - REMOVE LATER
    // for(int i=0; i < results.size(); i++)
    //     std::cout << results.at(i) << ' ';
    // std::cout << std::endl;

    if (validate_Place(input))
    {
        std::cout << "Hey that was a place!" << std::endl;
    }
    else if (validate_Replace(input))
    {
        std::cout << "Hey that was a replace!" << std::endl;
    }
    else if (results.at(0) == "save")
    {
        std::cout << "Hey that was a save!" << std::endl;
    }
    else if (results.at(0) == "quit")
    {
        std::cout << "Hey that was a quit!" << std::endl;
    }
    else {
        std::cout << "bzzzt! wrong input!" << std::endl;
    }
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

bool GameController::validate_Place(string input){
    // regex expression for pattern to be searched 
    std::regex regex("^place\s[ROYGBP][1-6]\sto\s[A-Z]\d+$");
    // flag type for determining the matching behavior (in this case on string objects)
    std::smatch m; 
    // regex_search that searches pattern in the string
    return std::regex_search(input, m, regex); 
}

bool GameController::validate_Replace(string input){
    // regex expression for pattern to be searched 
    std::regex regex("^replace\s[ROYGBP][1-6]$");
    // flag type for determining the matching behavior (in this case on string objects)
    std::smatch m; 
    // regex_search that searches pattern in the string
    return std::regex_search(input, m, regex); 
}