
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include <iostream>
#include "Node.h"

class LinkedList {
public:

   LinkedList();
   LinkedList(LinkedList& other);
   ~LinkedList();

   void printList(Node* n);

// we won't need addFront or insert, but do them for practise
   void addFront(Tile* tile);
   void addBack(Tile* tile);
   void insert(Tile* tile, int index);

   void removeFront();
   void removeBack();
   void remove(int index);
   void clear();

   Tile* getFront();
   Tile* getBack();
   Tile* get(int index);

   int findTileIndex(Tile* tile);

private:
   Node* head;
   Node* tail;
   int size;
};

#endif // ASSIGN2_LINKEDLIST_H
