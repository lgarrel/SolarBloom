#pragma once
#include "PhysicalEntity.h"

class Platform : public PhysicalEntity
{
public:
	void OnInitialize() override;
	void OnUpdate() override; 
	void OnCollision(Entity* other) override;
	void LoadAnimation() override;
};