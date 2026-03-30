#include "Fongus.h"
#include "TestScene.h"
#include "Animation.h"
#include "FongusCloud.h"

Fongus::Fongus() : Enemy(FONGUS_HP) {}

void Fongus::OnInitialize()
{
	SetKineticBody(false);
	Enemy::OnInitialize(); 
	SetTagEnemy(TagEnemy::TFongusR);
	SetRigidBody(true);
	mIsDead = false;

	mCloud = CreateEntity<FongusCloud>({ GetSize().x * 5, GetSize().y * 5 }, sf::Color::Red, 3);

	LoadAnimation();
}

void Fongus::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TAcid))
	{
		isActive1 = true;
	}

	if (collidedWith->IsTag(TestScene::TPlayer) && toxic)
	{
		isActive = true;
	}
}

void Fongus::OnUpdate()
{
	if (mIsDead)
	{
		GetScene<TestScene>()->GetAssetManager()->GetSound("DeadMonster")->play();
		mCloud->Destroy();
		Destroy();
		return;
	}

	Enemy::OnUpdate();
	
	if (isActive1)
	{
		mProgress1 += GetDeltaTime();
		if (canTakeDamage)
		{
			AddRemoveHP(-1);
			canTakeDamage = false;
		}
		else
		{
			if (mProgress1 >= mDelay1)
			{
				isActive1 = false;
				canTakeDamage = true;
				mProgress1 = 0.f;
			}
		}
	}

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
				SetHitbox(GetSize().x * 5, GetSize().y * 3);
				SetHitboxOffset(0, -GetSize().y);
				ChangeAnimation("Attack", "single");
				mCloud->ChangeAnimation("FongusCloud", "byRow");
				mCloud->SetPosition(GetPosition().x, GetPosition().y - GetSize().y);

				SetTagEnemy(TagEnemy::TFongusG);
				SetRigidBody(false);
				toxic = true;

				mActionTimer = 3.f;
				mActionState = 1;
				break;

			case 1:
				mCloud->SetPosition(-1000.f, -1000.f);

				SetHitbox(GetSize().x, GetSize().y);
				SetHitboxOffset(0, 0);

				SetTagEnemy(TagEnemy::TFongusR);
				SetRigidBody(true);
				toxic = false;

				mCooldownTimer = 2.f;//+ActionTimer
				mActionTimer = 3.f;
				mActionState = 0;
				break;
			}
		}
	}

	if (mAnimations->IsFinished())
	{
		ChangeAnimation("Idle", "single");
	}
}

void Fongus::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Fongus.json");
	SetTexture("Fongus");
	mAnimations->LoadAnimationSingle("Idle");
}