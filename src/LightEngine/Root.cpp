#include "Root.h"
#include "TestScene.h"
#include "Animation.h"

void Root::OnInitialize()
{
	SetKineticBody(false);
	Obstacle::OnInitialize();
	SetTagObstacle(TagObstacle::TRootR);
	SetHitbox(GetSize().x, GetSize().y);
	SetRigidBody(false);

	LoadAnimation();
}

void Root::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TPlayer) && dangerous)
	{
		isActive = true;
	}
}

void Root::OnUpdate()
{
	if (isActive)
	{
		mProgress += GetDeltaTime();
		if (canDealDamage)
		{
			player->TransitionTo(Player::TakingDamage);
			canDealDamage = false;
		}
		else
		{
			if (mProgress >= mDelay)
			{
				isActive = false;
				canDealDamage = true;
				mProgress = 0.f;
			}
		}
	}

	if (mCooldownTimer > 0.f)
	{
		mCooldownTimer -= GetDeltaTime();
	}
	else
	{
		mActionTimer -= GetDeltaTime();
		if (mActionTimer <= 0.f)
		{
			switch (mActionState)
			{
			case 0:
				SetPosition(GetPosition().x, GetPosition().y - GetSize().y / 2);

				SetTagObstacle(TagObstacle::TRootG);
				dangerous = true;

				mActionTimer = 3.f;
				mActionState = 1;
				break;

			case 1:
				SetPosition(GetPosition().x, GetPosition().y + GetSize().y / 2);

				SetTagObstacle(TagObstacle::TRootR);
				dangerous = false;

				mCooldownTimer = 1.f;//+ActionTimer
				mActionTimer = 3.f;
				mActionState = 0;
				break;
			}
		}
	}
}

void Root::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Root.json");
	SetTexture("Root");
	mAnimations->LoadAnimationSingle("Idle");
}
