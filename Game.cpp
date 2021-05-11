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