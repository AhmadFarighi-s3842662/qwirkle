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

        // methods to modify player hand
        bool removeFromHand(string t);
        void addToHand(Tile* t);

    private:
        string name;
        int score;
        LinkedList* hand;
};