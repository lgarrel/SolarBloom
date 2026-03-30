#include "Wall.h"
#include "TestScene.h"
#include "Animation.h"

void Wall::OnInitialize()
{
	SetRigidBody(true);
	Obstacle::OnInitialize();
	SetTagObstacle(TagObstacle::TWall);
	SetHitbox(GetSize().x, GetSize().y);

	LoadAnimation();
}

void Wall::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TAcid))
	{
		mIsActive = true;
	}
}

void Wall::OnUpdate()
{
	if (mHP <= 0)
	{
		if (mAnimations->GetCurrentAnimation() != "Death")
		{
			ChangeAnimation("Death", "single");
			GetScene<TestScene>()->GetAssetManager()->GetSound("DeadMonster")->play();
		}
		if (mAnimations->IsFinished())
			Destroy();

		return;
	}

	if(mIsActive)
	{
		mProgress += GetDeltaTime();
	}

	if (mProgress >= mDelay)
	{
		mIsActive = false;
		mProgress = 0.f;
		mHP--;
	}

}

void Wall::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/ThornWall.json");
	SetTexture("ThornWall");
	mAnimations->LoadAnimationSingle("Idle");
}
