#include "SpriteComponent.h"
#include "Actor.h"
#include "Math.h"

#include <SDL_image.h>

ASpriteComponent::ASpriteComponent(AActor* owner, int drawOrder)
	: AComponent{ owner }, DrawOrder { drawOrder }
{
	TexWidth = 0;
	TexHeight = 0;
	Texture = nullptr;
}

ASpriteComponent::~ASpriteComponent()
{

}

void ASpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (Texture)
	{
		SDL_Rect r;

		r.w = static_cast<int>(TexWidth * Owner->Scale);
		r.h = static_cast<int>(TexHeight * Owner->Scale);

		r.x = static_cast<int>(Owner->Position.X - r.w / 2);
		r.y = static_cast<int>(Owner->Position.Y - r.h / 2);

		SDL_RenderCopyEx(
			renderer,
			Texture,
			nullptr,
			&r,
			AMath::ToDegree(Owner->Rotation),
			nullptr,
			SDL_FLIP_NONE);
	}
}

void ASpriteComponent::SetTexture(SDL_Texture* texture)
{
	Texture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &TexWidth, &TexHeight);
}
