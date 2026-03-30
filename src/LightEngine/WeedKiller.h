#pragma once
#include "Entity.h"
#include "Weapon.h"

class WeedKiller : public Weapon
{
	bool playSound = false;
	float mSoundDelay = 0.25f;
	float mProgressSound = 0.f;
public:
	void OnInitialize() override;
	void OnUpdate() override;
	void FixedUpdate(float dt) override;
	void OnDestroy() override;
	void Shoot() override;
};

