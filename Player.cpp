// #include <string>
#include "Player.h"

#define MAX_PLAYER_HAND_SIZE 6

// Construct Player object with specified name and score of 0
Player::Player(string n) 
    : name(n) {
        hand = new LinkedList();
        score = 0;
    }

Player::~Player() {
    // will this result in a double deletion of tiles? i assume not since it is 
    // deleting nodes with pointers to tiles rather than tiles themselves :V
    delete hand;
}

string Player::getName() {
    return name;
}

int Player::getScore() {
    return score;
}

void Player::setScore(int s) {
    score = s;
}

string Player::getHand() {
    return hand->toString();
}

/*
* checks if player's hand contains specified tile
* returns false if tile does not exist in player hand
*/
bool Player::hasTile(Tile* t) {
    bool tileExistence = false;
    if (hand->contains(t)) {
        tileExistence = true;
    }
    return tileExistence;
}

/* 
* removes specified string representation of tile from player hand if it exists
* returns false if tile does not exist in hand
*/
bool Player::removeFromHand(string s) {
    bool tileExistence = false;
    int index = -1;
    for (int i = 0; i < hand->getSize(); ++i) {
        // this relies on `s` being correctly formatted/validated after input to coincide with tilecode definition
        if (hand->get(i)->toString().compare(s) == 0) {
            index = i;
            tileExistence = true;
        }
    }
    if (tileExistence) {
        // removes last instance of `s` in player hand (can be maximum of 2)
        hand->remove(index);
    }
    return tileExistence;
}

/*
* removes specified tile if it exists in player's hand
* returns false if tile does not exist in hand
*/
bool Player::removeFromHand(Tile* t) {
    bool successful = false;
    if (hasTile(t)) {
        int i = hand->findTileIndex(t);
        std::cout << "removing " + t->toString() << " at index " << i << std::endl;
        hand->remove(i);
        successful = true;
    }
    return successful;
}

/* 
* adds to hand only if hand is not currently full (6 tile limit)
* returns false on unsuccessful addition of specified tile
*/
bool Player::addToHand(Tile* t) {
    bool successful = false;
    if (hand->getSize() < MAX_PLAYER_HAND_SIZE) {
        hand->addBack(t);
        successful = true;
    }
    return successful;
}



