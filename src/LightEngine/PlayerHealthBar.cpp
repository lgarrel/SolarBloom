#include "PlayerHealthBar.h"
#include "Player.h"
#include "Debug.h"
#include "Camera.h"
#include "TestScene.h"

void PlayerHealthBar::UpdateUI() 
{
	if (!pOwner || mDisplay == false)
		return;

	Camera cam = pOwner->GetScene<TestScene>()->GetCam();
	sf::Vector2f centerCam = cam.GetView()->getCenter();

	int currentHp = pOwner->GetCurrentHP();
	int maxHp = pOwner->GetMaxHP();

	for (int i = 0; i < currentHp; ++i)
	{
		Debug::DrawCircle(centerCam.x - 610 + i * 45, centerCam.y - 325, 15, sf::Color(100, 255, 0));
	}

	for (int i = currentHp; i < maxHp; ++i)
	{
		Debug::DrawCircle(centerCam.x - 610 + i * 45, centerCam.y - 325, 15, sf::Color(0, 75, 0));
	}
}
