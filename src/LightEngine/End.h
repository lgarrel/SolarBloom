#pragma once
#include "Entity.h"

class Player;

class End : public Entity
{
	float mScrollSpeed;
	bool isTriggered = false;
	float mAnimationDuration = 3.f;
	float mProgress = 0.f;

	bool isAnimationTriggered = false;

	float mDelayBeforeAnimation = 3.f;
	float mProgressDelay = 0.f;
	Player* pOwner;

	float mProgressToDestroyPlayer = 0.f;

	bool isHydroDestroyed = false;

	bool mEndTheGame = false;
	float mEndTimer;
public:
	void OnInitialize() override;
	void OnUpdate() override;
	void FixedUpdate(float dt) override;
	void OnCollision(Entity* pOther) override;
};

