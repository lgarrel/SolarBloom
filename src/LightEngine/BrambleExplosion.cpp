#include "BrambleExplosion.h"
#include "Animation.h"

void BrambleExplosion::OnInitialize()
{
	SetPosition(-1000.f, -1000.f);

	mKineticBody = false;
	SetRigidBody(false);
	mHitbox.isActive = false;

	LoadAnimation();
}

void BrambleExplosion::FixedUpdate(float dt)
{
	if (mAnimations->IsFinished())
	{
		SetPosition(-1000.f, -1000.f);
	}
}

void BrambleExplosion::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/BrambleExplosion.json");
	SetTexture("BrambleExplosion");
	mAnimations->LoadAnimationByRow("Dissipate");
}
