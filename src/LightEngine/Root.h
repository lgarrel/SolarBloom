#pragma once
#include "Obstacle.h"
class Root : public Obstacle
{
	float mDelay = 1.f;
	float mProgress = 0.f;
	bool isActive = false;
	bool canDealDamage = true;

	float mActionTimer = 3.f;
	float mCooldownTimer = 0.f;
	int mActionState = 0;
	bool dangerous = false;

public:
	void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override;
	void OnUpdate() override;
	void LoadAnimation() override;
};