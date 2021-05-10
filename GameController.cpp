#include "GameController.h"

GameController::GameController()
{
    // Starts with a nullptr, as it needs to get the player names input.
    game = nullptr;
}

GameController::~GameController()
{
    if (game != nullptr)
    {
        delete game;
    }
}