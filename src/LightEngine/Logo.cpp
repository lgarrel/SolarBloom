#include "Logo.h"
#include "TestScene.h"
#include "Camera.h"

void Logo::OnInitialize()
{
	SetTag((int)TestScene::TLogo);

	SetTexture("Logo");
	mShape.setTexture(mTexture);
}

void Logo::OnUpdate()
{
	Camera& pCam = GetScene<TestScene>()->GetCam();

	sf::Vector2f camPos = pCam.GetView()->getCenter();

	SetPosition(camPos.x, -1000);
}