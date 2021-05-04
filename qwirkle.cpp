
#include "LinkedList.h"

#include <iostream>

#define EXIT_SUCCESS    0

void testLinkedListFunction();

int main(void) {
   testLinkedListFunction();

   std::cout << "TODO: Implement Qwirkle!" << std::endl;

   std::cout << "Richard messing around!" << std::endl;

   return EXIT_SUCCESS;
}

void testLinkedListFunction(){
   LinkedList* list = new LinkedList();
   Tile* r1 = new Tile('R',1);
   Tile* r2 = new Tile('R',2);
   Tile* r3 = new Tile('R',3);
   Tile* r4 = new Tile('R',4);
   Tile* r5 = new Tile('R',5);
   Tile* r6 = new Tile('R',6);
   list->addFront(r3);
   list->addFront(r2);
   list->addFront(r1);
   list->addBack(r5);
   list->addBack(r6);
   list->insert(r4,3);
   list->printList();
   list->remove(1);
   list->printList();
   list->removeBack();
   list->removeFront();
   list->printList();
   delete r1;
   delete r2;
   delete r3;
   delete r4;
   delete r5;
   delete r6;
   delete list;
}
