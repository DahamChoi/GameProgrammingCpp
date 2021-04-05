#include "AnimSpriteComponent.h"
#include "Actor.h"
#include <SDL_image.h>

AAnimSpriteComponent::AAnimSpriteComponent(AActor* owner, int drawOrder)
	: ASpriteComponent{ owner, drawOrder }
{
	CurrentFrame = 0.f;
	AnimFPS = 0.f;
}

void AAnimSpriteComponent::Update(float deltaTime)
{
	ASpriteComponent::Update(deltaTime);

	if (AnimTextures.size() > 0)
	{
		CurrentFrame += AnimFPS * deltaTime;

		while (CurrentFrame >= AnimTextures.size())
		{
			CurrentFrame -= AnimTextures.size();
		}

		SetTexture(AnimTextures[static_cast<int>(CurrentFrame)]);
	}
}

void AAnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	AnimTextures = textures;
}
