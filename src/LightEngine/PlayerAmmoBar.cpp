#include "PlayerAmmoBar.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "TestScene.h"
#include "Player.h"
#include "Weapon.h"
#include "Debug.h"
#include "Camera.h"

void PlayerAmmoBar::UpdateUI() 
{
	if (!pOwner || mDisplay == false)
		return;

	sf::Vector2f playerPos = pOwner->GetPosition(); 
	sf::Vector2f playerSize = pOwner->GetSize();  

	Camera cam = pOwner->GetScene<TestScene>()->GetCam();

	sf::Vector2f centerCam = cam.GetView()->getCenter();

	Weapon* currentWeapon = pOwner->GetCurrentEquipedWeapon();
	std::vector<Weapon*> allWeapons = pOwner->GetAllWeapons();

	if (!currentWeapon || allWeapons.size() <= 0)
		return;

	float ratio = currentWeapon->GetRatioMunition(); 

	for (Weapon* w : allWeapons)
	{
		if (w->IsTag(TestScene::TGun)) 
		{ 
			int currentAmmos = w->GetCurrentAmmos();

			for (int i = 0; i < currentAmmos; ++i)  
			{
				Debug::DrawCircle(centerCam.x - 610 + i * 45, centerCam.y - 275, 15, sf::Color(0, 150, 255)); 
			} 

			for (int i = currentAmmos; i < w->GetMaxAmmos(); ++i)
			{
				Debug::DrawCircle(centerCam.x - 610 + i * 45, centerCam.y - 275, 15, sf::Color(0, 0, 75));
			}

			continue;
		}  

		if (w->IsTag(TestScene::TWeedKiller) && w->GetIsEquiped() == true) 
		{
			Debug::DrawFilledRectangle(playerPos.x - playerSize.x * 0.3f, playerPos.y - playerSize.y * 0.5f - 20, { 50, 12 }, sf::Color(150, 0, 0, 255)); 
			Debug::DrawFilledRectangle(playerPos.x - playerSize.x * 0.3f, playerPos.y - playerSize.y * 0.5f - 20, { 50 * ratio, 12 }, sf::Color::Yellow); 

			continue;
		}
	}

	
}

