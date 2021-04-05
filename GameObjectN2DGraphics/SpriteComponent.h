#pragma once

#include "Component.h"

class ASpriteComponent : public AComponent
{
public:
	ASpriteComponent(class AActor* owner, int drawOrder = 100);
	~ASpriteComponent();
	
	virtual void Draw(class SDL_Renderer* renderer);
	virtual void SetTexture(class SDL_Texture* texture);

public:
	class SDL_Texture* Texture;

	int DrawOrder;
	int TexWidth;
	int TexHeight;
};

