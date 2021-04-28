
#include "LinkedList.h"

#include <iostream>

#define EXIT_SUCCESS    0


using std::cout;
using std::cin;
using std::endl;

void startNewGame();

void startNewGame() {
   cout << "Starting a New Game!" << endl;
}




int main(void) {
   cout << "Welcome to Quirkle!" << endl << "-------------------" << endl;
   bool finish = false;
   while (!finish) {
         cout << "Menu" << endl << "----" << endl;
         cout << "1. New Game" << endl;
         cout << "2. Load Game" << endl;
         cout << "3. Credits (Show student information)" << endl;
         cout << "4. Quit" << endl;
         int selection = 0;
         cin >> selection;
         switch (selection) {
            case 0:
               cin.clear();
               cin.ignore(100,'\n');
               cout << "Invalid input" << endl;
               break;
            case 1:
               startNewGame();
               finish = true;
               break;
            default:
               cout << "ok?" << endl;
         }
}
   


   LinkedList* list = new LinkedList();
   delete list;

   std::cout << "TODO: Implement Qwirkle!" << std::endl;

   return EXIT_SUCCESS;
}
