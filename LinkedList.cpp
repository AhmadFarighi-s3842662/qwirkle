
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
   tail = nullptr;
   size = 0;
}

// The deep copy constructor and clear methods are adapted from this post:
// https://stackoverflow.com/a/34963321

LinkedList::LinkedList(LinkedList& other) {
   if (other.head == nullptr)
   {
      head = tail = nullptr;
   }
   else {
   head = new Node(*other.head);
   Node* tempOther = new Node(*other.head->next);
   Node* temp = head;
      while (tempOther != nullptr){
         temp->next = new Node(tempOther->tile, temp, nullptr);
         temp = temp->next;
         tempOther = tempOther->next;
      }
   tail = temp;
   }

}

LinkedList::~LinkedList() {
   if (size != 0)
   {
      Node* n = head;
      Node* next = nullptr;
      int counter = 0;

      // Actually, do I even need the counter?
      while (n != nullptr && counter < size) {
      next = n->next;
      delete n;
      n = next;
      counter++;
      }
   }
}

std::string LinkedList::toString()
{
   if (size > 0){
      std::string str = "";
      Node* n = head;
      while (n != NULL){
         str + n->tile->toString() + ",";
         n = n->next;
      }
      str + "/n";
   }
   else{
      std::cout << "This list is empty!" << std::endl;
   }

   return "TODO (LinkedList::toString())";
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
      if (index == 0){
         removeFront();
      }
      else if (index == size){
         removeBack();
      }
      else{
         Node* n = head;
         int counter = 0;
            while (n != nullptr && counter < index) {
            n = n->next;
            counter++;
            }
         n->previous->next = n->next;
         n->next->previous = n->previous;
         delete n;
         size--;
      }
   }
}

void LinkedList::clear(){
   Node* n = head;
   while (n != nullptr){
      Node* del = n;
      n = n->next;
      delete del;
      size--;
   }
   head = tail = nullptr;
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
      counter++;
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

   while (n != nullptr && counter < size && n->tile != tile) {
      n = n->next;
      counter++;
   }
   if (n == nullptr){
      index = -1;
   }
   else {
      index = counter;
   }
   return index;
}

int LinkedList::getSize(){
   return size;
}