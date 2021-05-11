#include "Game.h"

#include <iostream>

Game::Game(int playerCount)
{
    this->board = new Board;
    this->tileBag = new LinkedList();
    this->pCount = 0;
    this->players = new Player*[playerCount]{};
    this->currentPlayer = nullptr;

    // Filling the bag with 72 tiles, coloursArray should be GC'd after
    char colorsArray[NUM_COLOURS] {RED,ORANGE,YELLOW,GREEN,BLUE,PURPLE};
    for (int colour = 0; colour < NUM_COLOURS; colour++)
    {
        // Forgot the offset as shapes go 1-6 not 0-5
        for (int shape = 1; shape < NUM_SHAPES+1; shape++)
        {
            Tile* tile = new Tile(colorsArray[colour], shape);
            // Will just call the add method twice instead of putting in a loop
            tileBag->addFront(tile);
            tileBag->addFront(tile);
            delete tile;
        }
    }
    // shuffle the contents around
    srand(time(NULL));
    for (size_t i = 0; i < 256; i++)
    {
        int rando = rand() % 72;
        tileBag->addFront(tileBag->get(rando));
        tileBag->remove(rando+1);
        
    }

}

Game::Game(Game& other)
{
    this->board = new Board(*other.board);
    this->tileBag = new LinkedList(*other.tileBag);
    this->players = new Player*[other.pCount]{};
    for (int i = 0;i<other.pCount;i++){
        this->addPlayer(other.getPlayer(i));
    }
    currentPlayer = new Player(*other.currentPlayer);
}

Game::~Game()
{
    delete board;
    delete tileBag;
    for (int i = 0;i<this->pCount;i++){
        delete getPlayer(i);
    }
    delete players;
    
    if(currentPlayer == nullptr){
        delete currentPlayer;
    }
}

void Game::dealPlayerTiles()
{
    for(int x = 0; x<getPlayerCount(); x++){
        // Don't forget to get rid of this magic number later
        for (size_t i = 0; i < 6; i++)
        {
            getPlayer(x)->addToHand(tileBag->getFront());
            tileBag->removeFront();
        }
    }
}

void Game::printGame()
{
    // Debug prints, remove later.
    std::cout << tileBag->getSize() << std::endl;
    std::cout << tileBag->toString() << std::endl;

    //std::cout << "p1 hand: " << player1->getHand() << std::endl;
    //std::cout << "p2 hand: " << player2->getHand() << std::endl;
}

void Game::addPlayer(Player* newPlayer){
    Player* newP = new Player(*newPlayer);
    this->players[this->getPlayerCount()]=newP;
    this->pCount++;
}
int Game::getPlayerCount(){
    return this->pCount;
}
Player* Game::getPlayer(int i)
{
    return players[i];
}
Player* Game::getCurrentPlayer()
{
    return currentPlayer;
}
void Game::setCurrentPlayer(Player* playa)
{
    currentPlayer = playa;
}
Board* Game::getBoard()
{
    return board;
}

LinkedList* Game::getTileBag()
{
    return tileBag;
}
bool Game::placeTile(Tile& tile, char row, int col){
    bool inputValid = false;
    bool nCheck = false;
    bool eCheck = false;
    bool sCheck = false;
    bool wCheck = false;
    bool vCheck = false;
    bool hCheck = false;

    //Check if theres already a tile in desired location
    if(board->tileAt(row,col)==nullptr){
        //Check if theres a tile to the north
        if(board->tileAt(row-1,col)!=nullptr)
            nCheck=true;
        //Check if theres a tile to the east
        if(board->tileAt(row,col+1)!=nullptr)
            eCheck=true;
        //Check if theres a tile to the south
        if(board->tileAt(row+1,col)!=nullptr)
            sCheck=true;
        //Check if theres a tile to the west
        if(board->tileAt(row,col-1)!=nullptr)
            wCheck=true;

        //Check if there are no neighbours
        if(nCheck||eCheck||sCheck||wCheck){
            //Check if tile fits within entire vertical line
            if(nCheck||sCheck)
                vCheck=validateTilesInDirection(tile,row,col,1,0);
            //Check if tile fits within entire horizontal line
            if(eCheck||wCheck)
                hCheck=validateTilesInDirection(tile,row,col,0,1);
        }
    }

    //If vertical line was attempted and failed, or horizontal line was attempted and failed skip marking validaiton as true
    if(!(((nCheck||sCheck)&&vCheck==false)||((eCheck||wCheck)&&hCheck==false)))
        inputValid = true;

    return inputValid;
}

bool Game::validateTilesInDirection(Tile& tile, int originX, int originY, int moveX, int moveY){
    //set result to true
    //set similarAttribute to null
    //While loop{}
        //Check board at origin ++moveX,++moveY
        //if similarAttribute condition is null, set one here
        //if space matches established similarAttribute condition, continue loop
        //if space is empty end loop
        //if space fails to match established similarAttribute condition, end loop and set result to false
    //While loop{}
        //Check board at origin --moveX,--moveY
        //if similarAttribute condition is null, set one here
        //if space matches established similarAttribute condition, continue loop
        //if space is empty end loop
        //if space fails to match established similarAttribute condition, end loop and set result to false
    //return result
}