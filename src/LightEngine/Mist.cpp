#include "Mist.h"
#include "Animation.h"

void Mist::OnInitialize()
{
	SetPosition(-1000.f, -1000.f);

	mKineticBody = false;
	SetRigidBody(false);
	mHitbox.isActive = false;

	LoadAnimation();
}

void Mist::FixedUpdate(float dt)
{
	if (mAnimations->IsFinished())
	{
		SetPosition(-1000.f, -1000.f);
	}
}

void Mist::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Mist.json");
	SetTexture("Mist");
	mAnimations->LoadAnimationSingle("Idle");
}
