#pragma once
#include "Entity.h"
#define GRAVITY_ACCELERATION 9.81f * 50

class PhysicalEntity : public Entity
{
protected:
	bool mGravity = false;
	float mGravitySpeed = 0.f;
	bool mOnGround = false;

	float mDelay = 0.1f;
	float mProgress = 0.f;

	bool mIsReady = false;
public:
	void FixedUpdate(float dt) override;
	virtual void OnUpdate();
	void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override;
	void SetGravity(bool value) { mGravity = value; }
	void SetOnGround(bool value) { mOnGround = value; }
	void SwapGravity() { mGravity = !mGravity; }
	void Fall(float dt);
};