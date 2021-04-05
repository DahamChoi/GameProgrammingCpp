#include "Component.h"
#include "Actor.h"

AComponent::AComponent(AActor* owner, int updateOrder)
	: Owner{ owner }, UpdateOrder{ updateOrder }
{

}

AComponent::~AComponent()
{

}

void AComponent::Update(float deltaTime)
{
}
