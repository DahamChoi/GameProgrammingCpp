#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"

#include <SDL.h>
#include <SDL_image.h>

AGame::AGame() {}

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

    IMG_Init(IMG_INIT_PNG);
    
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

void AGame::AddActor(AActor* actor)
{
    PendingActors.push_back(actor);
}

void AGame::RemoveActor(AActor* actor)
{
    Actors.erase(
        find(PendingActors.begin(), PendingActors.end(), actor)
    );
}

SDL_Texture* AGame::GetTexture(const std::string& fileName)
{
    SDL_Texture* texture = ImageDataSource[fileName];
    if (texture != nullptr)
        return ImageDataSource[fileName];
    
    SDL_Surface* surf = IMG_Load(fileName.c_str());
    if (!surf)
    {
        SDL_Log("Failed to load texture file %s", fileName.c_str());
        return nullptr;
    }
    
    texture = SDL_CreateTextureFromSurface(Renderer, surf);
    SDL_FreeSurface(surf);
    if (!texture)
    {
        SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
        return nullptr;
    }

    return ImageDataSource[fileName] = texture;
}

void AGame::AddSprite(ASpriteComponent* sprite)
{
    Sprites.push(sprite);
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
}

void AGame::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), TicksCount + 16))
        ;

    float deltaTime = (SDL_GetTicks() - TicksCount) / 1000.f;
    TicksCount = SDL_GetTicks();

    if (deltaTime > 0.05f)
        deltaTime = 0.05f;

    for (auto actor : Actors)
    {
        actor->Update(deltaTime);
    }

    for (auto pending : PendingActors)
    {
        Actors.emplace_back(pending);
    }
    PendingActors.clear();

    for (auto it = Actors.begin(); it != Actors.end(); )
    {
        if ((*it)->State == AActor::DEAD)
        {
            Actors.erase(it++);
        }
        else
        {
            it++;
        }
    }
}

void AGame::GenerateOutput()
{
    // Buffer Clear
    SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);
    SDL_RenderClear(Renderer);

    // Draw Game Buffer
    SDL_SetRenderDrawColor(Renderer, 128, 128, 255, 255);

    // Swap Buffer
    SDL_RenderPresent(Renderer);
}

bool AGame::SpriteOrderCompareFunctionObject::operator()(
    const ASpriteComponent* s1, const ASpriteComponent* s2)
{
    return s1->DrawOrder > s2->DrawOrder;
}
