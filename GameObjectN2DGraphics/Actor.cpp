#include "Actor.h"
#include "Component.h"

AActor::AActor(AGame* game)
{
	State = EState::ACTIVE;
	Game = game;
	Position = { 0.f,0.f };
	Scale = 1.f;
	Rotation = 0.f;
}

AActor::~AActor()
{

}

void AActor::Update(float deltaTime)
{

}

void AActor::UpdateComponents(float deltaTime)
{
	for (auto component : Components)
	{
		component->Update(deltaTime);
	}
}

void AActor::UpdateActor(float deltaTime)
{

}

void AActor::AddComponent(AComponent* component)
{
	Components.push_back(component);
}

void AActor::RemoveComponent(AComponent* component)
{
	Components.erase(
		find(Components.begin(), Components.end(), component)
	);
}
