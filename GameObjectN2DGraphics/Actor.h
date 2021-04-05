#pragma once

#include "Vector2.h"

#include <vector>

class AActor
{
public:
	// AActor 상태
	enum class EState
	{
		ACTIVE,
		PAUSED,
		DEAD
	};

	// 생성자 및 소멸자
	AActor(class AGame* game);
	virtual ~AActor();

	// Game에서 호출하는 Update함수
	void Update(float deltaTime);

	// 액터에 부착된 모든 컴포넌트를 업데이트
	void UpdateComponents(float deltaTime);

	// 특정 액터에 특화된 업데이트 코드 (가상함수)
	virtual void UpdateActor(float deltaTime);

	void AddComponent(class AComponent* component);
	void RemoveComponent(class AComponent* component);

public:
	EState State;
	AVector2 Position;
	float Scale;
	float Rotation;

private:
	std::vector<class AComponent*> Components;
	class AGame* Game;
};

