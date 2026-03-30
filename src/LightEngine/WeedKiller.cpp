#include "WeedKiller.h"
#include "Player.h"
#include "Acid.h"
#include "TestScene.h"
#include "AssetManager.h"
#include "Animation.h"

void WeedKiller::OnInitialize()
{
	SetTag(TestScene::TWeedKiller); 
	mHitbox.isActive = false; 
	SetRigidBody(false);

	mShootingDelay = 0.025f;

	mMaxAmmos = 100;
	mAmmos = mMaxAmmos;
	mReloadTime = 0.f;
	mDelayBeforeReloading = 0.f;
}

void WeedKiller::OnUpdate()
{
	if (!pOwner)
		return;

	if (mIsEquiped == false)
		return;

	if (playSound)
	{
		GetScene<TestScene>()->GetAssetManager()->GetSound("WeedKiller")->play();
		playSound = false;
		mProgressSound = 0.f;
	}

	if (mProgressSound >= mSoundDelay)
	{
		GetScene<TestScene>()->GetAssetManager()->GetSound("WeedKiller")->stop();
	}

	if(mProgressSound < mSoundDelay)
	{
		mProgressSound += GetDeltaTime();
	}
}

void WeedKiller::FixedUpdate(float dt)
{
	if (!pOwner)
		return;

	if (mIsEquiped == false || pOwner->GetState() == Player::Dying)
	{
		GetScene<TestScene>()->GetAssetManager()->GetSound("WeedKiller")->stop();
		return;
		
	}

	ShootManager(sf::Keyboard::Key::Right, 0, 7);

	sf::Vector2f playerPos = pOwner->GetPosition();

	SetPosition(playerPos.x + pOwner->GetSize().x * 0.5f * pOwner->GetSide(), playerPos.y);
}

void WeedKiller::OnDestroy()
{
	SetOwner(nullptr);
}

void WeedKiller::Shoot()
{
	if (mAmmos <= 0)
		return;

	mProgressDelay = 0.f;

	if (pOwner != nullptr)
	{
		const char* currentAnim = pOwner->GetAnimations()->GetCurrentAnimation();
		int side = pOwner->GetSide();

		if (side == 1 && currentAnim != "AttackRight")
		{
			pOwner->ChangeAnimation("AttackRight", "single");
		}
		else if (side == -1 && currentAnim != "AttackLeft")
		{
			pOwner->ChangeAnimation("AttackLeft", "single");
		}

		Acid* a = CreateEntity<Acid>({10, 10}, sf::Color::Transparent, 2);

		a->SetOwner(this);
		a->SetPosition(GetPosition().x, GetPosition().y);
		a->SetPlayerSide(pOwner->GetSide());

		mShootingDelay = 0.025f;

		AddRemoveAmmo(-1);

		if (playSound == false && mProgressSound >= mSoundDelay)
		{
			playSound = true;
		}

		mProgressSound = 0.f;
	}
}
