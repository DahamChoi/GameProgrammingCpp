#pragma once

#include <vector>

#include "SpriteComponent.h"

class AAnimSpriteComponent : public ASpriteComponent
{
public:
	AAnimSpriteComponent(class AActor* owner, int drawOrder = 100);

	void Update(float deltaTime) override;

	void SetAnimTextures(const std::vector<class SDL_Texture*>& textures);

private:
	std::vector<class SDL_Texture*> AnimTextures;
	float CurrentFrame;

public:
	float AnimFPS;
};

