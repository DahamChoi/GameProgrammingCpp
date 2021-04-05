#include "BGSpriteComponent.h"
#include "Actor.h"

#include <SDL_image.h>

ABGSpriteComponent::ABGSpriteComponent(AActor* owner, int drawOrder)
	: ASpriteComponent{ owner, drawOrder }
{
	ScreenSize = { 0.f, 0.f };
	ScrollSpeed = 300.f;
}

void ABGSpriteComponent::Update(float deltaTime)
{
	ASpriteComponent::Update(deltaTime);

	for (auto& bg : BGTextures)
	{
		bg.Offset.X -= ScrollSpeed * deltaTime;
		if (bg.Offset.X < -ScreenSize.X)
			bg.Offset.X = (BGTextures.size() - 1) * ScreenSize.X - 1;
	}
}

void ABGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& bg : BGTextures)
	{
		Owner->Position.X = bg.Offset.X;
		ASpriteComponent::Draw(renderer);
	}
}

void ABGSpriteComponent::SetBGTexture(const std::vector<SDL_Texture*>& textures)
{
	for (int i = 0; i < textures.size(); i++)
	{
		BGTextures.emplace_back(BGTexture{
			textures[i], AVector2{ i * ScreenSize.X , 0.f }});
	}
}
