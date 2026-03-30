#include "BG.h"
#include "TestScene.h"
#include "Camera.h"

void BG::OnInitialize()
{
	SetTag((int)TestScene::TBG);

	SetTexture("BG");
	mShape.setTexture(mTexture);
}

void BG::OnUpdate()
{
	Camera& pCam = GetScene<TestScene>()->GetCam();

	sf::Vector2f camPos = pCam.GetView()->getCenter();

	SetPosition(camPos.x, camPos.y);
}
