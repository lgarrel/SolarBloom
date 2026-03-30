#pragma once
#include "Obstacle.h"
class Bridge : public Obstacle
{
	bool mGrowing = false;
	float mInitialSizeX = 0.f;
	float mSizeX = 0.f;
	int mGrowDistance = 5;
	int mGrowProgress = 0;
	bool mGrown = false;

	float mDuration = 0.25f;
	float mProgress = 0.f;

	float mRetractDuration = 0.25f;
	float mRetractProgress = 0.f;
	float mCooldown = 3.f;
	float mCooldownProgress = 0.f;

public:
	void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override;
	void OnUpdate() override;

	void LoadAnimation() override;
	void Grow();
	void Retract();
};