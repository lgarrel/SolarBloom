#pragma once
#include "Enemy.h"

#define BRAMBLE_HP 1

class BrambleExplosion;

class Bramble : public  Enemy
{
	float mExplosionDelay = 1.f;
	float mExplosionTimer = 0.f;
	bool mExplosionActive = false;
	float mProximityRadius = 0.f;
	bool isPlayerInProximity = false;

	BrambleExplosion* mExplosion;

public:
	Bramble();

	void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override;

	void OnUpdate() override;

	void LoadAnimation() override;

	bool IsPlayerInProximity();
	void Explose();
};