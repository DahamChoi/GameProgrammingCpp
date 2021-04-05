#pragma once

#include "SpriteComponent.h"
#include "Vector2.h"

#include <vector>

class ABGSpriteComponent : public ASpriteComponent
{
public:
	ABGSpriteComponent(class AActor* owner, int drawOrder = 10);

	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;

	void SetBGTexture(const std::vector<class SDL_Texture*>& textures);

public:
	AVector2 ScreenSize;
	float ScrollSpeed;

private:
	struct BGTexture
	{
		class SDL_Texture* Texture;
		AVector2 Offset;
	};

	std::vector<BGTexture> BGTextures;
};

