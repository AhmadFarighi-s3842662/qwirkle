
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include <iostream>
#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   void printList(Node* n);

// we won't need addFront or insert, but do them for practise
   void addFront(Tile* tile);
   void insert(Tile* tile, int index);
   void addBack(Tile* tile);

   void removeFront();
   void remove(int index);
   void removeBack();

   Tile* getFront();
   Tile* get(int index);
   Tile* getBack();

   int findTileIndex(Tile* tile);

private:
   Node* head;
   int size;
};

#endif // ASSIGN2_LINKEDLIST_H
