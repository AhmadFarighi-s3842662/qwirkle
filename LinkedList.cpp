
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
   tail = nullptr;
   size = 0;
}

LinkedList::LinkedList(LinkedList& other) {
   // This is scuffed, will fix after dinner.
   // if (other.head == nullptr)
   // {
   //    return;
   // }
   // Node* newHead = other.head;
   // head = nullptr;
   // tail = nullptr;
   // size = other.size;
}

LinkedList::~LinkedList() {
   if (size != 0)
   {
      Node* n = head;
      Node* next = nullptr;
      int counter = 0;

      while (n != nullptr && counter < size) {
      next = n->next;
      delete n;
      n = next;
      }
   }
}

void LinkedList::printList(Node *n)
{
   if (size > 0){
      while (n != NULL){
         std::cout << n->tile << " ";
         n = n->next;
      }
   }
   else{
      std::cout << "This list is empty!" << std::endl;
   }
}

void LinkedList::addFront(Tile* tile){
   if(size == 0){
      Node* newNode = new Node(tile, nullptr, nullptr);
      head = tail = newNode;
      size++;
   }
   else {
      Node* newNode = new Node(tile, nullptr, head);
      head->previous = newNode;
      head = newNode;
      size++;
   }
}

void LinkedList::addBack(Tile* tile){
   if(size == 0){
      addFront(tile);
   }
   else {
      Node* newNode = new Node(tile, tail, nullptr);
      tail->next = newNode;
      tail = newNode;
      size++;
   }
}

void LinkedList::insert(Tile* tile, int index){
   if(size == 0){
      addFront(tile);
   }
   else{
      Node* n = head;
      int counter = 0;

      while (n != nullptr && counter < index) {
      n = n->next;
      }
      if (counter == size){
         addBack(tile);
      }
      else {
      Node* newNode = new Node(tile,n->previous, n->next);
      n->previous->next = newNode;
      n->next->previous = newNode;
      size++;
      }
   }
}

void LinkedList::removeFront(){
   if(size == 0){
      std::cout << "Cannot removeF: this list is empty!" << std::endl;
   }
   else{
      head = head->next;
      delete head->previous;
      head->previous = nullptr;
      size--;
   }
}

void LinkedList::removeBack(){
   if(size == 0){
      std::cout << "Cannot removeB: this list is empty!" << std::endl;
   }
   else{
      tail = tail->previous;
      delete tail->next;
      tail->next = nullptr;
      size--;
   }
}

void LinkedList::remove(int index){
   if(size == 0){
   std::cout << "Cannot remove: this list is empty!" << std::endl;
   }
   else {
      Node* n = head;
      int counter = 0;
      while (n != nullptr && counter < index) {
      n = n->next;
      }
      n->previous->next = n->next;
      n->next->previous = n->previous;
      delete n;
      size--;
   }
}

Tile* LinkedList::getFront(){
   Tile* tile = nullptr;
   if (head != nullptr)
   {
      tile = head->tile;
   }
   else {
      std::cout << "Cannot getF: this list is empty!" << std::endl;
   }
   return tile;
}

Tile* LinkedList::getBack(){
   Tile* tile = nullptr;
   if (tail != nullptr)
   {
      tile = tail->tile;
   }
   else {
      std::cout << "Cannot getB: this list is empty!" << std::endl;
   }
   return tile;
}

Tile* LinkedList::get(int index){
   Tile* tile = nullptr;
   if (size != 0)
   {
      Node* n = head;
      int counter = 0;
      while (n != nullptr && counter < index) {
      n = n->next;
      }
      tile = n->tile;
   }
   else {
      std::cout << "Cannot get: this list is empty!" << std::endl;
   }
   return tile;
}

int LinkedList::findTileIndex(Tile* tile){
   Node* n = head;
   int index = 0;
   int counter = 0;
   bool found = false;

   while (n != nullptr && counter < size && n->tile != tile) {
      n = n->next;
   }
   if (n == nullptr){
      index = -1;
   }
   else {
      index = counter;
   }
   return index;
}