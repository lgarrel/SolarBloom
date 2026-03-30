#include "Nenuphloat.h"
#include "TestScene.h"
#include "Player.h"
#include "Animation.h"

void Nenuphloat::OnInitialize()
{
	mDefaultSize = GetSize();
	mGrownSize = { mDefaultSize.x * 5, mDefaultSize.y};

	mKineticBody = false;
	Ally::OnInitialize();
	SetTagAlly(TNenuphloatR);
	SetRigidBody(false);
	SetHitbox(mDefaultSize.x, mDefaultSize.y);

	LoadAnimation();
}

void Nenuphloat::OnUpdate()
{
	Ally::OnUpdate();

	if(grown && mProgress <= mDuration)
		mProgress += GetDeltaTime();

	if (grown && mProgress >= mDuration)
	{
		Retract();
	}
}

void Nenuphloat::FixedUpdate(float dt)
{
	if (grown == true)
		return;

	CheckClosed();
}

void Nenuphloat::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TWater))
	{
		Grow();
	}
}

void Nenuphloat::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Nenuphloat.json");
	SetTexture("Nenuphloat");
	mAnimations->LoadAnimationSingle("IdleBud");
}

bool Nenuphloat::CheckClosed()
{
	if (mAnimations->GetCurrentAnimation() == "Closing")
	{
		if (mAnimations->IsFinished())
		{
			mShape.setSize(mDefaultSize);
			SetHitbox(mDefaultSize.x, mDefaultSize.y);
			SetPosition(mPosition.x, mPosition.y);
			ChangeAnimation("IdleBud", "single");
			return true;
		}
		return false;
	}
	return false;
}

void Nenuphloat::Grow()
{
	mPosition = GetPosition();

	SetRigidBody(true);
	SetTagAlly(TNenuphloatG);
	if (!grown)
	{
		grown = true;
		mShape.setSize(mGrownSize);
		SetHitbox(mGrownSize.x, mGrownSize.y / 4.f);
		SetPosition(mPosition.x, mPosition.y);
		ChangeAnimation("Opening", "single");
		GetScene<TestScene>()->GetAssetManager()->GetSound("Transition")->play();
	}
}

void Nenuphloat::Retract()
{
	SetRigidBody(false);
	SetTagAlly(TNenuphloatR);
	if (!grown)
		return;

	grown = false;
	mProgress = 0.f;
	ChangeAnimation("Closing", "single");
	GetScene<TestScene>()->GetAssetManager()->GetSound("Transition")->play();
}