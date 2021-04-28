
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
   size = 0;
}

LinkedList::~LinkedList() {
   // Will need to be a for loop that goes through the list until size, deleting
   // nodes.
}

void LinkedList::printList(Node* n){
    while (n != NULL) {
        std::cout << n->tile << " ";
        n = n->next;
    }
}

void LinkedList::addFront(Tile* tile){
   if (head == nullptr){
      Node* newNode = new Node(tile,nullptr);
      head = newNode;
      size++;
   }
   else {
      Node* newNode = new Node(tile, head);
      head = newNode;
      size++;
   }
}

void LinkedList::insert(Tile* tile, int index){
   Node* n = head;
   Node* previous = nullptr;
   int counter = 0;

   while (n != nullptr && counter < index) {
      previous = n;
      n = n->next;
   }

   if (head == nullptr){
      std::cout << "list was empty, creating first node\n";
      head = new Node (tile, nullptr);
   }

   else if(n == nullptr)
   {
      std::cout << "index was outside of list size, will add to end\n";
      Node* newNode = new Node(tile,nullptr);
      n = newNode;
      size++;
   }
   else{
      std::cout << "index was inside list size, will add to index "<< 
      counter << "\n";
      Node* newNode = new Node(tile,n);
      previous->next = newNode;
      n = newNode;
      size++;
   }
   
}