
#include "Node.h"

Node::Node(Tile* pTile, Node* pPrevious, Node* pNext)
{
   tile = pTile;
   previous = pPrevious;
   next = pNext;
}

Node::Node(Node& other)
{
   tile = other.tile;
   previous = other.previous;
   next = other.next;
}