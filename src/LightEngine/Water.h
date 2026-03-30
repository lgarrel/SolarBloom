#pragma once
#include "Entity.h"

class Player;

class Water : public Entity
{
	float mSurvivalTime = 3.f;
	float mProgress = 0.f;
public:
	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;
	void OnInitialize() override;
	void OnDestroy() override;
	void LoadAnimation() override;
};

