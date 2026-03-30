#include "Water.h"
#include "Player.h"
#include "TestScene.h"
#include "AssetManager.h"
#include "Animation.h"

void Water::OnUpdate()
{
	mProgress += GetDeltaTime();

	if(mProgress >= mSurvivalTime)
		Destroy();
}

void Water::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TPlayer) || collidedWith->IsTag(TestScene::TEnemy))  
		return;

	if (mAnimations->GetCurrentAnimation() != "Pop")
	{
		mHitbox.isActive = false;
		ChangeAnimation("Pop", "byRow");
		SetSpeed(0);
		GetScene<TestScene>()->GetAssetManager()->GetSound("Waterdrop")->play();
	}

	if (mAnimations->IsFinished())
	{
		Destroy();
	}
}

void Water::OnInitialize()
{
	SetTag(TestScene::TWater);

	SetRigidBody(false);

	SetSpeed(750);

	SetHitbox(GetSize().x, GetSize().y);

	LoadAnimation();
}

void Water::OnDestroy()
{
}

void Water::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Water.json");
	SetTexture("Water");
	mAnimations->LoadAnimationByRow("Water");
}
