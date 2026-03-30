#pragma once
#include "Entity.h"
#include "PlayerUI.h"

class DashUI : public Entity, public PlayerUI
{
public:
	void OnInitialize() override;
	void FixedUpdate(float dt) override;
	void OnUpdate() override;
	void LoadAnimation() override;
	void UpdateUI() override;
};

