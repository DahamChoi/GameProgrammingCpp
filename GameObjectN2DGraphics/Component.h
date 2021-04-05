#pragma once

class AComponent
{
public:
	AComponent(class AActor* owner, int updateOrder = 100);
	virtual ~AComponent();

	virtual void Update(float deltaTime);

public:
	int UpdateOrder;

protected:
	class AActor* Owner;
};

