#include "Vine.h"
#include "TestScene.h"
#include "Animation.h"

void Vine::OnInitialize()
{
	mDefaultSize = GetSize();
	mGrownSize = { mDefaultSize.x, mDefaultSize.y * 10};

	Ally::OnInitialize();
	SetTagAlly(TVineR);
	SetRigidBody(false);
	SetHitbox(GetSize().x, GetSize().y);

	LoadAnimation();
}

void Vine::OnUpdate()
{
	Ally::OnUpdate();

	if (mIsReady == false)
	{
		mDefaultPos = GetPosition();
		mIsReady = true;
	}
}

void Vine::FixedUpdate(float dt)
{
	if (grown == true || mClosed)
		return;

	mClosed = CheckClosed();
}

void Vine::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TWater))
	{
		if (!grown)
			Grow();
		else
			Retract();
	}
}

void Vine::Grow()
{
	SetTagAlly(TVineG);
	mPosition = GetPosition();

	if (grown)
		return;

	grown = true;
	mClosed = false;
	mShape.setSize(mGrownSize);
	SetHitbox(mGrownSize.x, mGrownSize.y);
	SetPosition(mDefaultPos.x, mDefaultPos.y - (mDefaultSize.y * 4));
	ChangeAnimation("Opening", "single");
	GetScene<TestScene>()->GetAssetManager()->GetSound("Transition")->play();
}

void Vine::Retract()
{
	SetTagAlly(TVineR);
	if (!grown)
		return;

	grown = false;
	ChangeAnimation("Closing", "single");
	GetScene<TestScene>()->GetAssetManager()->GetSound("Transition")->play(); 
}

bool Vine::CheckClosed()
{
	if (mAnimations->GetCurrentAnimation() == "Closing")
	{
		if (mAnimations->IsFinished())
		{
			mShape.setSize(mDefaultSize);
			SetHitbox(mDefaultSize.x, mDefaultSize.y);
			SetPosition(mDefaultPos.x, mDefaultPos.y); 
			return true;
		}
		return false;
	}
	return false;
}

void Vine::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Liane.json");
	SetTexture("Vine");
	mAnimations->LoadAnimationSingle("Closing");
}
