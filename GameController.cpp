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

GameController::GameController(int playerCount) {
    this->game = new Game(playerCount);
    this->pCount = playerCount;
    for (int i = 0; i < pCount; ++i) {
        addPlayer();
    }
    this->keepGoing = true;
}

GameController::~GameController() {
    if (game != nullptr) {
        delete game;
    }
}

void GameController::addPlayer() {
    string input = "";
    cout << "Player " << game->getPlayerCount() + 1 << " name: " << endl;
    cout << "> ";
    std::getline(std::cin, input);
    game->addPlayer(new Player(input));
}

void GameController::gameStart() {
    game->dealPlayerTiles();
    game->setCurrentPlayer(game->getPlayer(0));
}

void GameController::gameLoop() {
    while (keepGoing)
    {
        bool moveSuccess = false;
        // Print current state of the board
        // cout << game->getBoard()->toString() << endl;

        // Ask current player for thier move
        string input = askForPlayerMove();
        moveSuccess = validateMoveInput(input);
        // perform move if valid, if not step back

        // switch current player if move was a success
        if (moveSuccess == true)
        {
            if (game->getCurrentPlayer() == game->getPlayer(0))
            {
                game->setCurrentPlayer(game->getPlayer(1));
            }
            else
            {
                game->setCurrentPlayer(game->getPlayer(0));
            }
        }
    }
}

string GameController::askForPlayerMove() {
    cout << "Current player: " << game->getCurrentPlayer()->getName() << endl
         << "Player's hand: "
         << game->getCurrentPlayer()->getHand()->toString() << endl;
    
    string input = "";
    cout << "Move format example: place R0 to A1" << endl;
    cout << "Replace tile example: replace R0" << endl;
    cout << "save" << endl;
    cout << "quit" << endl;
    cout << "> ";

    std::getline(std::cin, input);
    cout << endl;
    return input;
}

// Need to update this to return a bool
bool GameController::validateMoveInput(string input) {
    bool moveSuccess = false;

    // This block borrowed and modified from: 
    // https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
    std::istringstream iss(input);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    // End derived block

    //DEBUG PRINTS - REMOVE LATER
    // for(int i=0; i < results.size(); i++)
    //     std::cout << results.at(i) << ' ';
    // std::cout << std::endl;

    if (validate_Place(input)) {
        // Valid place command given
        std::cout << "Hey that was a place!" << std::endl;
        makeAMove(results.at(1), results.at(3));

    } else if (validate_Replace(input)) {
        // Valid replace command given
        std::cout << "Hey that was a replace!" << std::endl;
        moveSuccess = replaceATile(results.at(1));

    } else if (validate_save(results)) {
        // Because validate_save() is true, we know there is a second token
        std::string filename = results.at(1);

        if (game->saveGame(filename)) {
            std::cout << "Game successfully saved" << std::endl;
        } else {
            std::cout << "Sorry, there was an error while saving the game"
                      << std::endl;
        }
    } else if (results.size() > 0 && results.at(0) == "quit") {
        // Valid quit command given
        std::cout << "Hey that was a quit!" << std::endl;
        keepGoing = false;
    } else {
        // Invalid command given
        std::cout << "bzzzt! wrong input!" << std::endl;
    }

    return moveSuccess;
}
// Need to update this to return a bool
bool GameController::makeAMove(string tileSTR, string moveSTR) {
    bool success = false;

    // DEBUG
    std::cout << tileSTR << std::endl;
    std::cout << moveSTR << std::endl;

    string tile = tileSTR;
    game->getCurrentPlayer()->removeFromHand(tile);

    string bodge = moveSTR.substr(1,2);
    int col = std::stoi(bodge);

    string bodge2 = tileSTR.substr(1,1);
    int shapeBodge = std::stoi(bodge2);

    Tile* mTile = new Tile(tileSTR.at(0), shapeBodge);
    game->placeTile(*mTile, moveSTR.at(0), col);

    return success;
}

bool GameController::replaceATile(string tileSTR) {
    Tile* rTile = new Tile(tileSTR);
    bool success = false;

    // Check if the player has that tile or not, if yes...
    if (game->getCurrentPlayer()->hasTile(rTile))
    {
        success = game->swapTile(rTile);
    }
    // If the action didn't succeed, we should tell the player
    if (success == false)
    {
        std::cout << "Replacement not successful." << std::endl;
        if (game->getTileBag()->getSize() < 1)
        {
            std::cout << "Tile bag is empty!" << std::endl;
        }
    }
    delete rTile;
    return success;
}

bool GameController::validate_Place(string input) {
    // regex expression for pattern to be searched 
    std::regex regex("^place [ROYGBP][1-6] at [A-Z][0-9]{1,2}$");
    // flag type for determining the matching behavior (in this case on string
    // objects)
    std::smatch m; 
    // regex_search that searches pattern in the string
    return std::regex_search(input, m, regex); 
}

bool GameController::validate_Replace(string input) {
    // regex expression for pattern to be searched 
    std::regex regex("^replace [ROYGBP][1-6]$");
    // flag type for determining the matching behavior (in this case on string
    // objects)
    std::smatch m; 
    // regex_search that searches pattern in the string
    return std::regex_search(input, m, regex); 
}

bool GameController::validate_save(std::vector<std::string>& input) {
    bool isValid = false;

    if (input.size() > 0) {
        isValid = input.size() == 2 && input.at(0) == "save";
    }

    return isValid;
}
