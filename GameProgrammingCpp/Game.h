#pragma once

#include "Vector2.h"

class AGame
{
public:
	AGame();

	bool Initialize();
	void RunLoop();
	void Shutdown();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	class SDL_Window* Window;
	class SDL_Renderer* Renderer;
	bool IsRunning;

	Vector2 BallPos{ 1024.f / 2.f, 768.f / 2.f };
	Vector2 BallVel{ 1.f, 1.f };

	Vector2 PaddlePos{ 30.f, 768.f / 2.f };
	int PaddleDirectionY{ 0 };

	unsigned int TicksCount{ 0 };

	const static int Thickness{ 15 };
	const static int PaddleHeight{ 75 };
};
