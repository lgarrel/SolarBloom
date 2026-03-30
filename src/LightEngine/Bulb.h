#pragma once
#include "Ally.h"

class Mist;

class Bulb : public Ally
{
	Mist* mMist;

public:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;

	void FixedUpdate(float dt) override;

	void LoadAnimation() override;
};