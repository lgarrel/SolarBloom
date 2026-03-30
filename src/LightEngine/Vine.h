#pragma once
#include "Ally.h"

class Vine : public Ally
{
	sf::Vector2f mDefaultSize = { 0.f, 0.f };
	sf::Vector2f mDefaultPos = { 0.f, 0.f };
	sf::Vector2f mGrownSize = { 0.f, 0.f };

	sf::Vector2f mPosition;

	bool grown = false;
	bool mClosed = true;

	bool mIsReady = false;

public:
	void OnInitialize() override;
	void OnUpdate() override;
	void FixedUpdate(float dt) override;
	void OnCollision(Entity* collidedWith) override;
	void Grow();
	void Retract();
	bool CheckClosed();

	void LoadAnimation() override;
};