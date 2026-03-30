#include "FongusCloud.h"
#include "Animation.h"

void FongusCloud::OnInitialize()
{
	SetPosition(-1000.f, -1000.f);

	mKineticBody = false;
	SetRigidBody(false);
	mHitbox.isActive = false;

	LoadAnimation();
}

void FongusCloud::FixedUpdate(float dt)
{
}

void FongusCloud::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/FongusCloud.json");
	SetTexture("FongusCloud");
	mAnimations->LoadAnimationByRow("FongusCloud");
}
