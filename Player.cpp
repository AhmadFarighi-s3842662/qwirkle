// #include <string>
#include "Player.h"

#define MAX_PLAYER_HAND_SIZE 6

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

bool Player::removeFromHand(Tile* t) {
    bool tileExistence = false;
    if (hand->contains(t)) {
        tileExistence = true;
        int i = hand->findTileIndex(t);
        hand->remove(i);
    }
    return tileExistence;
}

void Player::addToHand(Tile* t) {
    // maybe this should also be a boolean? I left it as void because adding to playerhand should be handled by game logic
    if (hand->getSize() < MAX_PLAYER_HAND_SIZE) {
        hand->addBack(t);
    }
}



