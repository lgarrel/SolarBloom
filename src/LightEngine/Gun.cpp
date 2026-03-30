#include "Gun.h"
#include "Player.h"
#include "Water.h"
#include "TestScene.h"
#include <iostream>
#include <SFML/Graphics.hpp>

void Gun::OnInitialize()
{
	SetTag(TestScene::TGun); 
	mHitbox.isActive = false;
	SetRigidBody(false);

	mMaxAmmos = 4;
	mAmmos = mMaxAmmos;
	mReloadTime = 1.f;
	mDelayBeforeReloading = 2.f;

	mShootingDelay = 0.5f;
	mIsEquiped = true;
}

void Gun::OnUpdate()
{
	if (!pOwner)
		return;

	ReloadManager();

	if (mIsEquiped == true)
		ShootManager(sf::Keyboard::Key::Right, 0, 7);
}

void Gun::FixedUpdate(float dt)
{
	if (!pOwner)
		return;

	if (mIsEquiped == false || pOwner->GetState() == Player::Dying)
	{
		return;
	}

	sf::Vector2f playerPos = pOwner->GetPosition();
	sf::Vector2f pos = this->GetPosition();

	sf::Vector2f finalDirection = { std::cos(mAngle) * pOwner->GetSide(), std::sin(mAngle) };

	float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::R); // pos vertical du joystick droit

	if (mDirection.y >= -0.995)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || y < -25)
		{
			mAngle -= 2 * dt; 
		}
	}

	if (mDirection.y <= 0.995)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || y > 25)
		{
			mAngle += 2 * dt; 
		} 
	}

	SetDirection(finalDirection.x, finalDirection.y);
}

void Gun::Shoot()
{
	if (mAmmos <= 0)
		return;

	mProgressDelay = 0.f;

	sf::Vector2f pos = GetPosition();

	Water* w = CreateEntity<Water>({24, 24}, sf::Color::White, 2);
	w->SetPosition(pos.x, pos.y);
	w->SetDirection(mDirection.x, mDirection.y); 
	mShootingDelay = 0.5f;

	AddRemoveAmmo(-1);
	GetScene<TestScene>()->GetAssetManager()->GetSound("PlayerShooting")->play(); 
}
