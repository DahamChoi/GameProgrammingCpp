#include "Game.h"
#include <SDL.h>

Game::Game()
{
    IsRunning = true;
    Window = nullptr;
}

bool Game::Initialize()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
        return false;
    }

    Window = SDL_CreateWindow(
        "Game Prgramming in C++ (C.1)",
        100,
        100,
        1024,
        768,
        0
    );
    if (!Window)
    {
        SDL_Log("Faield to create window: %s", SDL_GetError());
        return false;
    }
    
    return true;
}

void Game::RunLoop()
{
    while (IsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown()
{
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

void Game::ProcessInput()
{
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
}
