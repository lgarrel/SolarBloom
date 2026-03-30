#pragma once
#include "Entity.h"

class Player;

class Weapon : public Entity
{
protected:
	Player* pOwner;

	int mPlayerSide;

	int mMaxAmmos;
	int mAmmos;
	float mReloadTime;
	float mProgressReload = 0.f;

	float mDelayBeforeReloading;
	float mProgressDelay = 0.f;

	float mShootingDelay;

	bool mIsEquiped = false;

	void AddRemoveAmmo(int value);
public:
	virtual void SetOwner(Player* pOwner) { this->pOwner = pOwner; }
	virtual void Shoot() = 0;
	void OnDestroy() override;

	void ReloadManager();
	void ShootManager(sf::Keyboard::Key key, int valueJoystick1, int valueJoystick2);
	void ShootManager(sf::Mouse::Button mouseButton, int valueJoystick1, int valueJoystick2);

	int GetCurrentAmmos() { return mAmmos; }
	int GetMaxAmmos() { return mMaxAmmos; }
	float GetRatioMunition() { return (float) mAmmos / (float) mMaxAmmos; }
	int GetTag() { return mTag; }
	void SetMaxAmmos(int value) { mMaxAmmos = value; }
	void SetCurrentAmmos(int value) { mAmmos = value; }

	bool GetIsEquiped() { return mIsEquiped; }
	void SetIsEquiped(bool value) { mIsEquiped = value; }

	Player* GetOwner() {return pOwner; }
};

