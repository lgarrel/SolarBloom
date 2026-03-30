#pragma once
#include"Enemy.h"
#include <SFML/System/Vector2.hpp>

#define IVY_HP 1

class Ivy : public Enemy
{
	float mTimer = 2.f;
	float mCounter = 0.f;
	bool mPlayerInContact = false;

	float mInitialPosition;
	int mDirection = 1;
	float mSpeed = 50.f;
	bool posInitial = true;
	
public:
	Ivy();

	void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override;

	void OnUpdate() override;

	void LoadAnimation() override;

	void HandleAction();
};
