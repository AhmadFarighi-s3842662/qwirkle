#include "Game.h"

Game::Game(string p1, string p2)
{
    board = new Board;
    tileBag = new LinkedList;
    player1 = new Player(p1);
    player2 = new Player(p2);
    currentPlayer = nullptr;
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