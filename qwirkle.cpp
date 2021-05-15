#include "Game.h"
#include "GameController.h"
#include "LinkedList.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <vector>

#define EXIT_SUCCESS 0
#define NUM_PLAYERS 2

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::istringstream;

string promptUser();
void startNewGame();
bool loadGame();
void showCredits();
void terminateGame();

// Split inputString into tokens based on the locations of delimiter and return
// them as a vector
std::vector<string> splitString(string inputString, string delimiter);

// Returns user input as std::string which can be parsed as int, where required,
// using string stream (as demonstrated in menu)
string promptUser() {
    string input = "";
    cout << "> ";
    // cin >> input;
    std::getline(std::cin, input);
    return input;
}

void startNewGame() {
    cout << "Starting a New Game!" << endl;
    GameController* theGame = new GameController(NUM_PLAYERS);
    theGame->gameStart();
    theGame->gameLoop();
}

bool loadGame() {
    // Get the filename from the user
    cout << "Enter the filename from which to load a game" << endl;
    string filename = promptUser();

    bool success = false;
    std::vector<string> lines;

    // Attempt to read the file
    try {
        std::ifstream inFile;
        inFile.open(filename);

        // Check that the file exists and store the contents of the file
        if (inFile.good()) {
            // Store each line of the file in the vector
            while (!inFile.eof()) {
            string currLine;
            std::getline(inFile, currLine);
            lines.push_back(currLine);
            }
        }

        inFile.close();
    } catch (...) {
        // Error while reading file, success remains false
    }

    // Check that the format of the file is correct
    const int linesPerPlayer = 3;
    const int gameStateLines = 4;

    // Verify the file had enough lines in it as a sanity check
    if (lines.size() >= (linesPerPlayer * NUM_PLAYERS) + gameStateLines) {
        try {
            bool formatIsValid = true;
            char colorsArray[NUM_COLOURS] {RED, ORANGE, YELLOW, GREEN, BLUE,
                                           PURPLE};

            Player* players[NUM_PLAYERS];
            for (int i = 0; i < NUM_PLAYERS; ++i) {
                players[i] = nullptr;
            }

            // Create players
            for (int i = 0; i < NUM_PLAYERS; ++i) {
                string name = lines.at((i * linesPerPlayer) + 1);
                players[i] = new Player(name);

                // Set player's score
                int score = std::stoi(lines.at((i * linesPerPlayer) + 2));
                players[i]->setScore(score);

                // Fill player's hand
                std::vector<string> tileStrings =
                    splitString(lines.at((i * linesPerPlayer) + 3), ",");
                
                for (unsigned int j = 0; j < tileStrings.size(); ++j) {
                    char colour = tileStrings.at(j).at(0);
                    int shape = std::stoi(tileStrings.at(j).substr(1, 1));

                    // Verify that the colour and shape are valid
                    bool colourIsValid = false;
                    for (char c : colorsArray) {
                        if (colour == c) {
                            colourIsValid = true;
                        }
                    }

                    bool shapeIsValid = shape >= CIRCLE && shape <= CLOVER;

                    // If the colour/shape is invalid, the tile will still be
                    // added to the player's hand, however the format of the
                    // file will be considered invalid
                    formatIsValid = colourIsValid && shapeIsValid;

                    Tile* t = new Tile(colour, shape);
                    players[i]->addToHand(t);
                    delete t;
                }
            }

            // Create board
            Board board;

            // Create tile bag

            // Store current player

            // Create game

            if (formatIsValid) {
                success = true;
            }

            // Clean up memory
            for (int i = 0; i < NUM_PLAYERS; ++i) {
                if (players[i] != nullptr) {
                    delete players[i];
                }
            }

        } catch (...) {
            // Error occurred while constructing game, success remains false
        }
    }

    return success;
}

void terminationMessage() {
    cout << "Goodbye" << endl;
}

// bit ugly but who cares its just credits ¯\_(ツ)_/¯
void showCredits() {
    cout << "-------------------------------------" << endl;
    cout << "Name: Ahmad Seiam Farighi" << endl << "Student ID: s3842662"
         << endl << "Email: s3842662@student.rmit.edu.au" << endl << endl;

    cout << "Name: Daniel Marmion" << endl << "Student ID: s3842912" << endl
         << "Email: s3842912@student.rmit.edu.au" << endl << endl;

    cout << "Name: Richard Forsey" << endl << "Student ID: s3857811" << endl
         << "Email: s3857811@student.rmit.edu.au" << endl << endl;

    cout << "Name: Aaron Fisher" << endl << "Student ID: s3840619" << endl
         << "Email: s3840619@student.rmit.edu.au" << endl;
    cout << "-------------------------------------" << endl << endl;
}

int main(void) {
    cout << "Welcome to Quirkle!" << endl << "-------------------" << endl;
    atexit(terminationMessage);

    std::vector<string> a = splitString("B1@F9, B3@F10, P1@G9", ", ");
    for (int i = 0; i < 3; ++i) {
        cout << a.at(i) << endl;
    }

    bool shouldDisplayMenu = true;
    do {
        cout << "Menu" << endl << "----" << endl;
        cout << "1. New Game" << endl;
        cout << "2. Load Game" << endl;
        cout << "3. Credits (Show student information)" << endl;
        cout << "4. Quit" << endl << endl;
        
        istringstream iss (promptUser());
        int selection = 0;
        iss >> selection;

        cout << endl;

        if (iss.fail()) {
            if (iss.eof()) {
                shouldDisplayMenu = false;
            } else {
                cout << "Invalid Input. Please enter a number from 1-4."
                     << endl;
            }
        } else {
            if (selection == 1) {
                startNewGame();

                // assumes menu should not repeat after game is completed
                // (incorrect assumption)
                shouldDisplayMenu = false;       
            } else if (selection == 2) {
                loadGame();

                // assumes menu should not repeat after game is completed
                // (incorrect assumption)
                shouldDisplayMenu = false;
            } else if (selection == 3) {
                showCredits();
            } else if (selection == 4) {
                shouldDisplayMenu = false;
            } else {
                cout << "Sorry, that isn't an option. "
                     << "Please enter a number from 1-4." << endl;
            }
        }
    } while (shouldDisplayMenu);

    LinkedList* list = new LinkedList();
    delete list;

    return EXIT_SUCCESS;
}

std::vector<string> splitString(string inputString, string delimiter) {
    std::vector<string> tokens;

    // Test whether or not there is at least one occurence of delimiter in the
    // string
    if (inputString.find(delimiter) != string::npos) {
        int startpos = 0;
        while (inputString.find(delimiter, startpos) != string::npos) {
            int delimiterLoc = inputString.find(delimiter, startpos);
            int tokenLength = delimiterLoc - startpos;

            tokens.push_back(inputString.substr(startpos, tokenLength));

            startpos = delimiterLoc + delimiter.size();
        }

        // Account for the remaining substring after the last delimiter
        tokens.push_back(inputString.substr(startpos));
    } else {
        // Delimiter is not in string, so add only the original string to the
        // vector
        tokens.push_back(inputString);
    }

    return tokens;
}