#include "Game.h"

#include <iostream>
#define ASCII_VALUE_A 65

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
    bool invCheck = false;
    bool hCheck = false;
    bool inhCheck = false;
    int rowIndex = rowCharToIndex(row);    

    //Check if theres already a tile in desired location
    if(board->tileAt(row,col)==nullptr){
        //Check if theres a tile to the north
        if(board->tileAt(rowIndex-1,col)!=nullptr)
            nCheck=true;
        //Check if theres a tile to the east
        if(board->tileAt(rowIndex,col+1)!=nullptr)
            eCheck=true;
        //Check if theres a tile to the south
        if(board->tileAt(rowIndex+1,col)!=nullptr)
            sCheck=true;
        //Check if theres a tile to the west
        if(board->tileAt(rowIndex,col-1)!=nullptr)
            wCheck=true;

        //Check if there are no neighbours
        if(nCheck||eCheck||sCheck||wCheck){
            //Check if tile fits within entire vertical line
            if(nCheck||sCheck){
                vCheck=validateTilesInDirection(tile,rowIndex,col,1,0);
                invCheck=validateTilesInDirection(tile,rowIndex,col,-1,0);
            }
                
            //Check if tile fits within entire horizontal line
            if(eCheck||wCheck){
                hCheck=validateTilesInDirection(tile,rowIndex,col,0,1);
                inhCheck=validateTilesInDirection(tile,rowIndex,col,0,-1);
            }
        }
    }

    //If vertical line was attempted and failed, or horizontal line was attempted and failed skip marking validaiton as true
    if(!(((nCheck||sCheck)&&(vCheck&&invCheck))||((eCheck||wCheck)&&(hCheck&&inhCheck))))
        inputValid = true;

    if(inputValid)
        inputValid = board->placeTile(tile,row,col);

    return inputValid;
}

bool Game::validateTilesInDirection(Tile& tile, int originX, int originY, int moveX, int moveY){
    //set result to true
    bool result = true;
    //set similarAttribute to null
    string similarAttributeType = "";
    Colour similarColour = 'X';
    Shape similarShape = 0;
    int multiplier = 1;
    Tile* nextTile = board->tileAt(originX+moveX*multiplier,originY+moveY*multiplier);
    
    while(result && nextTile!=nullptr){ 
        //if similarAttribute condition is null, set one here
        if (similarAttributeType == ""){
            //If tiles share colour, set similar attribute to colour
            if (nextTile->getColour() == tile.getColour()){
                similarAttributeType == "COLOUR";
                similarColour == tile.getColour();
            }
            //If tile is sharing shape and colour, its a duplicate and should be rejected,
            //otherwise if its only matching shape, set similar attribute to shape
            if(nextTile->getShape() == tile.getShape()){
                similarAttributeType = (similarAttributeType == "COLOUR") ? "" : "SHAPE";
                similarShape = (similarAttributeType == "SHAPE") ? tile.getShape() : 0;
            }
        }
        //If similarAttribute is still empty, tile does not match required conditions
        if(similarAttributeType == ""){
            result = false;
        }else{
            //If tiles share the same colour, check that shape is different
            if(similarAttributeType == "COLOUR")
                result = (nextTile->getShape()!=tile.getShape()) ? true : false;
            //If tiles share the same shape, check that colour is different
            if(similarAttributeType == "SHAPE")
                result = (nextTile->getColour()!=tile.getColour()) ? true : false;
        }
        //Move to next tile
        multiplier += 1;
        nextTile = board->tileAt(originX+moveX*multiplier,originY+moveY*multiplier);
    }

}

int Game::rowCharToIndex(char row) {
    row = std::toupper(row);

    /*
     * ASCII uppercase characters begin from 65, so subtracting 65 from the
     * character's value produces the corresponding row index in the vector.
     * 
     * A useful table can be found here:
     * https://www.w3schools.com/charsets/ref_html_ascii.asp
     */ 
    return (int) row - ASCII_VALUE_A;
}