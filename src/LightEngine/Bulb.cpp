#include "Bulb.h"
#include "Animation.h"
#include "TestScene.h"
#include "Mist.h"

void Bulb::OnInitialize()
{
	Ally::OnInitialize();
	SetTagAlly(TBulb);
	SetRigidBody(false);
	SetHitbox(GetSize().x, GetSize().y);

	mMist = CreateEntity<Mist>({ GetSize().x * 8.f, GetSize().y * 3.f }, sf::Color::Red, 5);

	LoadAnimation();
}

void Bulb::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TWater))
	{
		ChangeAnimation("Release", "single");
		mMist->ChangeAnimation("Dissipate", "single");
	}
}

void Bulb::FixedUpdate(float dt)
{
	if (mAnimations->IsFinished())
	{
		ChangeAnimation("Idle", "single");
	}

	if (mMist->GetAnimations()->GetCurrentAnimation() == "Dissipate")
		return;	

	mMist->SetPosition(GetPosition().x, GetPosition().y - GetSize().y);
}

void Bulb::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Bulbe_Lumina.json");
	SetTexture("Bulb");
	mAnimations->LoadAnimationSingle("Idle");
}

void Bulb::OnUpdate()
{
	Ally::OnUpdate();
}
