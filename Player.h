#include <string>

#include "LinkedList.h"
#include "Tile.h"

using std::string;
class Player {
public:
    // constructor & destructor
    Player(string n);
    ~Player();

    // setters & getters
    void setScore(int s);
    int getScore();
    string getName();
    string getHand();

    // methods to modify/access player hand
    bool hasTile(Tile* t);
    bool removeFromHand(string t);
    bool removeFromHand(Tile* t);
    bool addToHand(Tile* t);

private:
    string name;
    int score;
    LinkedList* hand;
};