#pragma once
#include "Obstacle.h"

class Wall : public Obstacle
{
	int mHP = 3;

	float mDelay = 0.5f;
	float mProgress = 0.f;
	bool mIsActive = false;

public:
	void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override;
	void OnUpdate() override;

	void LoadAnimation() override;
};