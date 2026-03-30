#include "Weapon.h"
#include <iostream>
#include "TestScene.h"
#include "AssetManager.h"

void Weapon::AddRemoveAmmo(int value)
{
	mAmmos += value;

	if (mAmmos > mMaxAmmos)
		mAmmos = mMaxAmmos;

	if (mAmmos < 0)
	{
		mAmmos = 0;
	}
}

void Weapon::OnDestroy()
{
}

void Weapon::ReloadManager()
{
	if (mProgressDelay >= mDelayBeforeReloading) 
	{
		mProgressReload += GetDeltaTime();

		if (mProgressReload >= mReloadTime && mAmmos < mMaxAmmos)
		{
			if (IsTag(TestScene::TGun))
			{
				GetScene<TestScene>()->GetAssetManager()->GetSound("ReloadWater")->play();
			}

			AddRemoveAmmo(1);
			mProgressReload = 0.f;
		}
	}
	else
	{
		mProgressDelay += GetDeltaTime();
	}
}

void Weapon::ShootManager(sf::Keyboard::Key key, int valueJoystick1, int valueJoystick2)
{
	if (sf::Keyboard::isKeyPressed(key) || sf::Joystick::isButtonPressed(valueJoystick1, valueJoystick2))
	{
		if (mShootingDelay <= 0)
		{
			if (pOwner != nullptr)
			{
				Shoot();
			}	
		}
	}

	if (mShootingDelay < 0)
	{
		mShootingDelay = 0;
	}
	else
		mShootingDelay -= GetDeltaTime();
}

void Weapon::ShootManager(sf::Mouse::Button mouseButton, int valueJoystick1, int valueJoystick2)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button(mouseButton)) || sf::Joystick::isButtonPressed(valueJoystick1, valueJoystick2))
	{
		if (mShootingDelay <= 0)
		{
			if (pOwner != nullptr)
				Shoot();
		}
	}

	if (mShootingDelay < 0)
	{
		mShootingDelay = 0;
	}
	else
		mShootingDelay -= GetDeltaTime();
}

