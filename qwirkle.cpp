#include "LinkedList.h"
#include "Game.h"
#include "GameController.h"

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

#define EXIT_SUCCESS 0

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
   cin >> input;
   return input;
}

/*
 * maybe also have a method called like conductGame(Game* g) which takes in a
 * game `state`/instance and conducts the gameplay loop i.e startnewGame calls
 * Game constructor and then calls conductGame() with the newly created Game
 * object.
 * 
 * loadGame reads file and instantiates Game object with the deserialized
 * contents which is then passed to conductGame().
 */
void startNewGame() {
   cout << "Starting a New Game!" << endl;
   GameController* theGame = new GameController(2);
   theGame->gameStart();
   theGame->gameLoop();
}

bool loadGame() {
   cout << "Which game would you like to load?" << endl;
   return false;
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
            cout << "Invalid Input. Please enter a number from 1-4." << endl;
         }
      } else {
         if (selection == 1) {
            startNewGame();

            // assumes menu should not repeat after game is completed (incorrect
            // assumption)
            shouldDisplayMenu = false;       
         } else if (selection == 2) {
            loadGame();

            // assumes menu should not repeat after game is completed (incorrect
            // assumption)
            shouldDisplayMenu = false;
         } else if (selection == 3) {
            showCredits();
         } else if (selection == 4) {
            shouldDisplayMenu = false;
         } else {
            cout << "Sorry, that isn't an option. Please enter a number from 1-4"
                 << endl;
         }
      }
   } while (shouldDisplayMenu);

   LinkedList* list = new LinkedList();
   delete list;

   return EXIT_SUCCESS;
}
