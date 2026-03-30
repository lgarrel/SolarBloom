#include "DashUI.h"
#include "Animation.h"
#include "Camera.h"
#include "TestScene.h"
#include "Player.h"

void DashUI::OnInitialize()
{
	mKineticBody = false;
	SetRigidBody(false);
	mHitbox.isActive = false;

	LoadAnimation();
}

void DashUI::FixedUpdate(float dt)
{

}

void DashUI::OnUpdate()
{
	if (!pOwner)
		return;

	if (mDisplay == false)
	{

		ChangeColor(sf::Color::Transparent);
	}
	else
		ChangeColor(sf::Color::White);

	Camera cam = pOwner->GetScene<TestScene>()->GetCam();
	sf::Vector2f centerCam = cam.GetView()->getCenter();

	if (pOwner->GetProgressDashReload() <= 0)
	{
		if (mAnimations->GetCurrentAnimation() != "Full")
			ChangeAnimation("Full", "byRow");
	}
	else
	{
		if (mAnimations->GetCurrentAnimation() != "Recharge" || mAnimations->IsFinished())
			ChangeAnimation("Recharge", "byRow");
	}
	SetPosition(centerCam.x - 400, centerCam.y - 300);
}

void DashUI::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Dash.json");
	SetTexture("Dash");
	mAnimations->LoadAnimationByRow("Full");
}

void DashUI::UpdateUI()
{

}
