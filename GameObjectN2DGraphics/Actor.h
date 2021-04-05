#pragma once

#include "Vector2.h"

#include <vector>

class AActor
{
public:
	// AActor ����
	enum class EState
	{
		ACTIVE,
		PAUSED,
		DEAD
	};

	// ������ �� �Ҹ���
	AActor(class AGame* game);
	virtual ~AActor();

	// Game���� ȣ���ϴ� Update�Լ�
	void Update(float deltaTime);

	// ���Ϳ� ������ ��� ������Ʈ�� ������Ʈ
	void UpdateComponents(float deltaTime);

	// Ư�� ���Ϳ� Ưȭ�� ������Ʈ �ڵ� (�����Լ�)
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

