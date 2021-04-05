#pragma once

#include <vector>
#include <map>
#include <string>
#include <queue>

class AGame
{
private:
	struct SpriteOrderCompareFunctionObject
	{
		bool operator()(const ASpriteComponent* s1, const ASpriteComponent* s2);
	};

public:
	AGame();

	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class AActor* actor);
	void RemoveActor(class AActor* actor);

	class SDL_Texture* GetTexture(const std::string& fileName);
	void AddSprite(class ASpriteComponent* sprite);

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	class SDL_Window* Window{ nullptr };
	class SDL_Renderer* Renderer{ nullptr };
	bool IsRunning{ true };

	std::vector<class AActor*> PendingActors;
	std::vector<class AActor*> Actors;

	std::priority_queue<
		class ASpriteComponent*,
		std::vector<ASpriteComponent*>,
		SpriteOrderCompareFunctionObject> Sprites;

	std::map<std::string, class SDL_Texture*> ImageDataSource;

	unsigned int TicksCount{ 0 };
};
