#pragma once
#include "Enemy.h"


#define THORN_HP 1

class Thorn : public Enemy
{
    float mDelay = 1.f;
    float mProgress = 0.f;
    bool isActive = false;
	bool canDealDamage = true;

    float mDelay1 = 0.5f;
    float mProgress1 = 0.f;
    bool isActive1 = false;
	bool canTakeDamage = true;

    float mProximityRadius = 0.f;
    float mActionTimer = 0.f;
    bool mActionTriggered = false;
    float mCooldownTimer = 0.f;

	bool mPlayerLeft = false;

public:
    Thorn();

    void OnInitialize() override;
    void OnCollision(Entity* collidedWith) override;

    void FixedUpdate(float dt) override;
    void OnUpdate() override;

    void LoadAnimation() override;

    bool IsPlayerInProximity();
};