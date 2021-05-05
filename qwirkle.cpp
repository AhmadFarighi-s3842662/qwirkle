
#include "LinkedList.h"

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

#define EXIT_SUCCESS    0


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

string promptUser() {
   string input = "";
   cout << "> ";
   cin >> input;
   return input;
}

void startNewGame() {
   cout << "Starting a New Game!" << endl;
}

bool loadGame() {
   cout << "Which game would you like to load?" << endl;
   return false;
}

void terminateGame() {
   cout << "Goodbye" << endl;
}



int main(void) {
   cout << "Welcome to Quirkle!" << endl << "-------------------" << endl;
   atexit (terminateGame);
   while(true) {
         cout << "Menu" << endl << "----" << endl;
         cout << "1. New Game" << endl;
         cout << "2. Load Game" << endl;
         cout << "3. Credits (Show student information)" << endl;
         cout << "4. Quit" << endl;
         
         istringstream iss (promptUser());
         int selection = 0;
         iss >> selection;
         if (iss.fail()) {
            if (iss.eof()) {
               exit (EXIT_SUCCESS);
            }
            cout << "Invalid Input. Please enter a number from 1-4." << endl;
         } else {
            if (selection == 1) {
               startNewGame();
            } else if (selection == 2) {
               loadGame();
            } else if (selection == 3) {
               cout << "Showing credits" << endl;
            } else if (selection == 4) {
               return EXIT_SUCCESS;
            } else {
               cout << "Sorry, that isn't an option. Please enter a number from 1-4" << endl;
            }
         }
   }
         



   


   LinkedList* list = new LinkedList();
   delete list;

   std::cout << "TODO: Implement Qwirkle!" << std::endl;

   return EXIT_SUCCESS;
}
