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
        bool formatIsValid = false;

        // Create players

        // Create board

        // Create tile bag

        // Store current player

        // Create game

        if (formatIsValid) {
            success = true;
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
    cout << "Name: Ahmad Seiam Farighi" << endl << "Student ID: s3842662" << endl
    << "Email: s3842662@student.rmit.edu.au" << endl << endl;

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
