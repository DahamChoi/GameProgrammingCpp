#include "Game.h"
#include <SDL.h>

AGame::AGame()
{
    IsRunning = true;
    Window = nullptr;
    Renderer = nullptr;
}

bool AGame::Initialize()
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

    Renderer = SDL_CreateRenderer(
        Window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!Renderer)
    {
        SDL_Log("Faield to create Renderer: %s", SDL_GetError());
        return false;
    }
    
    return true;
}

void AGame::RunLoop()
{
    while (IsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void AGame::Shutdown()
{
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();
}

void AGame::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            IsRunning = false;
            break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
    {
        IsRunning = false;
    }

    PaddleDirectionY = 0;
    if (state[SDL_SCANCODE_W])
    {
        PaddleDirectionY -= 1;
    }
    if (state[SDL_SCANCODE_S])
    {
        PaddleDirectionY += 1;
    }
}

void AGame::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), TicksCount + 16))
        ;

    float deltaTime = (SDL_GetTicks() - TicksCount) / 1000.f;
    TicksCount = SDL_GetTicks();

    if (deltaTime > 0.05f)
        deltaTime = 0.05f;

    if (PaddleDirectionY < 0.f)
    {
        if (PaddlePos.y - PaddleHeight / 2 > Thickness)
            PaddlePos.y = PaddlePos.y + PaddleDirectionY * 300.f * deltaTime;
    }
    else if (PaddleDirectionY > 0.f)
    {
        if (PaddlePos.y + PaddleHeight / 2 < 768 - Thickness)
            PaddlePos.y = PaddlePos.y + PaddleDirectionY * 300.f * deltaTime;
    }

    BallPos.x = BallPos.x + BallVel.x * 300.f * deltaTime;
    BallPos.y = BallPos.y + BallVel.y * 300.f * deltaTime;

    if (BallPos.y - (Thickness / 2) < Thickness && BallVel.y < 0.f)
    {
        BallVel.y *= -1.f;
    }

    if (BallPos.y + (Thickness / 2) > 768 - Thickness && BallVel.y > 0.f)
    {
        BallVel.y *= -1.f;
    }

    if (BallPos.x + (Thickness / 2) > 1024 - Thickness && BallVel.x > 0.f)
    {
        BallVel.x *= -1.f;
    }

    if ((BallPos.y + (Thickness / 2) > PaddlePos.y - PaddleHeight &&
        BallPos.y - (Thickness / 2) < PaddlePos.y + PaddleHeight) &&
        BallPos.x - (Thickness / 2) < PaddlePos.x + Thickness &&
        BallVel.x < 0.f)
    {
        BallVel.y *= -1.f;
        BallVel.x *= -1.f;
    }
}

void AGame::GenerateOutput()
{
    // Buffer Clear
    SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);
    SDL_RenderClear(Renderer);

    // Draw Game Buffer
    static SDL_Rect TopWall{
        0,
        0,
        1024,
        Thickness
    };

    static SDL_Rect BottomWall{
        0,
        768 - Thickness,
        1024,
        Thickness
    };

    static SDL_Rect RightWall{
        1024 - Thickness,
        0,
        Thickness,
        768
    };

    SDL_Rect Ball{
        static_cast<int>(BallPos.x - Thickness / 2),
        static_cast<int>(BallPos.y - Thickness / 2),
        Thickness,
        Thickness
    };

    SDL_Rect Paddle{
        static_cast<int>(PaddlePos.x - Thickness / 2),
        static_cast<int>(PaddlePos.y - PaddleHeight / 2),
        Thickness,
        PaddleHeight
    };

    SDL_SetRenderDrawColor(Renderer, 128, 128, 255, 255);
    SDL_RenderFillRect(Renderer, &TopWall);
    SDL_RenderFillRect(Renderer, &BottomWall);
    SDL_RenderFillRect(Renderer, &RightWall);
    SDL_RenderFillRect(Renderer, &Ball);
    SDL_RenderFillRect(Renderer, &Paddle);

    // Swap Buffer
    SDL_RenderPresent(Renderer);
}
