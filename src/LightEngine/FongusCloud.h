#pragma once
#include "Entity.h"

class FongusCloud : public Entity
{

public:
	void OnInitialize() override;
	void FixedUpdate(float dt) override;
	void LoadAnimation() override;
};

