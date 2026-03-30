#pragma once
#include"Enemy.h"

#define FONGUS_HP 2

class FongusCloud;

class Fongus : public  Enemy
{
	float mDelay = 1.f;
	float mProgress = 0.f;
	bool isActive = false;
	bool canDealDamage = true;

	float mDelay1 = 0.5f;
	float mProgress1 = 0.f;
	bool isActive1 = false;
	bool canTakeDamage = true;

	float mActionTimer = 3.f;
	float mCooldownTimer = 0.f;
	int mActionState = 0;
	bool toxic = false;

	FongusCloud* mCloud;

public:
	Fongus();

	void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override;
	void OnUpdate() override;

	void LoadAnimation() override;
};