#include "PhysicalEntity.h"
#include <iostream>

void PhysicalEntity::FixedUpdate(float dt)
{
	if(mOnGround == false && mHitbox.hasHitbox)
		Fall(dt);
}

void PhysicalEntity::OnUpdate()
{
	if (mProgress < mDelay)
	{
		mProgress += GetDeltaTime();
		return;
	}
	if (mIsReady == false)
	{
		mIsReady = true;
		SetIsHitboxActive(true);
	}
}

void PhysicalEntity::OnInitialize()
{
	SetIsHitboxActive(false);
}

void PhysicalEntity::OnCollision(Entity* collidedWith)
{
}

void PhysicalEntity::Fall(float dt)
{
	if (mGravity == false)
	{
		mGravitySpeed = 0.f;
		return;
	}

	mGravitySpeed += GRAVITY_ACCELERATION * dt;
	
	sf::Vector2f pos = GetPosition(); 
	float newPosY = pos.y + mGravitySpeed * dt;
	SetPosition(pos.x, newPosY);
}
