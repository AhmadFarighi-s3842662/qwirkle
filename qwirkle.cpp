
#include "LinkedList.h"
#include "Player.h"

#include <iostream>

#define EXIT_SUCCESS    0

void testLinkedListFunction();

int main(void) {
   testLinkedListFunction();
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
   list->addBack(r4);
   list->addBack(r5);
   list->addBack(r6);
   std::cout << list->toString() << std::endl; 
   list->remove(1);
   std::cout << list->toString() << std::endl; 
   list->removeBack();
   list->removeFront();
   std::cout << list->toString() << std::endl; 
   std::cout << "-------" << std::endl;
   std::cout << "Testing contains()" << std::endl;
   Tile* t1 = new Tile('R', 3);
   Tile* t2 = new Tile('R', 5);
   if (t1->equals(*r1)) { std::cout << "yes they match fella" << std::endl;}
   if (list->contains(t1)) {std::cout << "Yes " << t1->toString() << " is in this list" << std::endl;}
   if (list->contains(t2)) {std::cout << "Yes " << t2->toString() << " is in this list" << std::endl;}
   std::cout << "Testing addToHand() & removeFromHand()" << std::endl;
   Player* p = new Player("Me");
   p->addToHand(r1);
   p->addToHand(r2);
   p->addToHand(r3);
   p->addToHand(r4);
   p->addToHand(r5);
   p->addToHand(r6);
   p->addToHand(t1);
   std::cout << p->getHand() << std::endl;
   p->removeFromHand(t2);
   std::cout << p->getHand() << std::endl;
   if (p->removeFromHand(t2)) {std::cout << "Double removal, incorrect" << std::endl;}
   p->removeFromHand("R1");
   std::cout << p->getHand() << std::endl;
   if (p->hasTile(r1)) {std::cout << "Player p has R1" << std::endl;} else {std::cout << "Player p does not have R1" << std::endl;}
   p->removeFromHand(r4);
   p->removeFromHand(r2);
   p->removeFromHand(r3);
   std::cout << p->getHand() << std::endl;
   p->removeFromHand(r6);
   std::cout << "." << std::endl;
   if (p->removeFromHand(r6)) {std::cout << "Double removal, incorrect" << std::endl;}


   delete r1;
   delete r2;
   delete r3;
   delete r4;
   delete r5;
   delete r6;
   delete t1;
   delete t2;
   delete p;
   delete list;
}
