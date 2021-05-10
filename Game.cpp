#include "Game.h"

#include <iostream>

Game::Game(string p1, string p2)
{
    board = new Board;
    tileBag = new LinkedList;
    player1 = new Player(p1);
    player2 = new Player(p2);
    currentPlayer = nullptr;

    // Filling the bag with 72 tiles, coloursArray should be GC'd after
    char colorsArray[NUM_COLOURS] {RED,ORANGE,YELLOW,GREEN,BLUE,PURPLE};
    for (int colour = 0; colour < NUM_COLOURS; colour++)
    {
        for (int shape = 0; shape < NUM_SHAPES; shape++)
        {
            Tile* tile = new Tile(colorsArray[colour], shape);
            // Will just call the add method twice instead of putting in a loop
            tileBag->addFront(tile);
            tileBag->addFront(tile);
        }
    }
    // shuffle the contents around
    srand(time(NULL));
    for (size_t i = 0; i < 256; i++)
    {
        int rando = rand() % 72;
        Tile* temp = new Tile(*tileBag->get(rando));
        tileBag->remove(rando);

        tileBag->addFront(temp);
        
    }

    // Might aswell fill player hands too. Change the 6 to a const later
    for (size_t i = 0; i < 6; i++)
    {
        player1->addToHand(tileBag->getFront());
        tileBag->removeFront();

        player2->addToHand(tileBag->getFront());
        tileBag->removeFront();
    }
}

Game::Game(Game& other)
{
    board = new Board(*other.board);
    tileBag = new LinkedList(*other.tileBag);
    player1 = new Player(*other.player1);
    player2 = new Player(*other.player2);
    currentPlayer = new Player(*other.currentPlayer);
}

Game::~Game()
{
    delete board;
    delete tileBag;
    delete player1;
    delete player2;
    // Do I need to make this check for nullptr first?
    delete currentPlayer;
}

void Game::printGame()
{
    // Debug prints, remove later.
    std::cout << tileBag->getSize() << std::endl;
    std::cout << tileBag->toString() << std::endl;

    std::cout << "p1 hand: " << player1->getHand() << std::endl;
    std::cout << "p2 hand: " << player2->getHand() << std::endl;
}