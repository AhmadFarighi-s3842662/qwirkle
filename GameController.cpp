#include "GameController.h"

#include <iostream>
#include <string>
#include <regex>
#include <limits>

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
    std::getline(std::cin, input);
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
    string input = askForPlayerMove();
    validateMoveInput(input);

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

    // cout << game->getBoard()->toString() << endl;
}

string GameController::askForPlayerMove(){
    cout << "Current player: " << game->getCurrentPlayer()->getName() << endl
         << "Player's hand: " << game->getCurrentPlayer()->getHand()->toString() << endl;
    string input = "";
    cout << "Move format example: place R0 to A1" << endl;;
    cout << "Repalce tile example: replace R0" << endl;;
    cout << "save" << endl;;
    cout << "quit" << endl;;
    cout << "> ";

    std::getline(std::cin, input);
    cout << endl;
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
        makeAMove(results.at(1), results.at(3));
    }
    else if (validate_Replace(input))
    {
        std::cout << "Hey that was a replace!" << std::endl;
        replaceATile(results.at(1));
    }
    else if (validate_save(results))
    {
        std::cout << "Hey that was a save!" << std::endl;
        // TODO extract filename from input and pass it along
        game->saveGame("");
    }
    else if (results.at(0) == "quit")
    {
        std::cout << "Hey that was a quit!" << std::endl;
    }
    else {
        std::cout << "bzzzt! wrong input!" << std::endl;
        askForPlayerMove();
    }
}

void GameController::makeAMove(string tileSTR, string moveSTR){
    std::cout << tileSTR << std::endl;
    std::cout << moveSTR << std::endl;

    string tile = tileSTR;
    game->getCurrentPlayer()->removeFromHand(tile);

    string bodge = moveSTR.substr(1,2);
    int col = std::stoi (bodge);

    string bodge2 = tileSTR.substr(1,1);
    int shapeBodge = std::stoi (bodge2);

    Tile* mTile = new Tile(tileSTR.at(0), shapeBodge);
    game->placeTile(*mTile,moveSTR.at(0),col);
}

void GameController::replaceATile(string tileSTR){
    std::cout << tileSTR << std::endl;

    game->getCurrentPlayer()->removeFromHand(tileSTR);
    game->getTileBag()->addBack(new Tile(tileSTR));
    game->getCurrentPlayer()->addToHand(game->getTileBag()->getFront());
    game->getTileBag()->removeFront();

    std::cout << game->getCurrentPlayer()->getHand()->toString() << std::endl;
}

bool GameController::validate_Place(string input){
    // regex expression for pattern to be searched 
    std::regex regex("^place [ROYGBP][1-6] to [A-Z][0-9]{1,2}$");
    // flag type for determining the matching behavior (in this case on string objects)
    std::smatch m; 
    // regex_search that searches pattern in the string
    return std::regex_search(input, m, regex); 
}

bool GameController::validate_Replace(string input){
    // regex expression for pattern to be searched 
    std::regex regex("^replace [ROYGBP][1-6]$");
    // flag type for determining the matching behavior (in this case on string objects)
    std::smatch m; 
    // regex_search that searches pattern in the string
    return std::regex_search(input, m, regex); 
}

bool GameController::validate_save(std::vector<std::string>& input) {
    return input.size() == 2 && input.at(0) == "save";
}