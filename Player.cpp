// #include <string>
#include "Player.h"

Player::Player(string n) 
    : name(n) {
        hand = new LinkedList();
        score = 0;
    }

Player::~Player() {
    delete hand;
}

string Player::getName() {
    return name;
}

void Player::setName(string n) {
    name = n;
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



