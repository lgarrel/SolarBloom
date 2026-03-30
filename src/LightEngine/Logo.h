#pragma once
#include "Entity.h"

class Logo : public Entity
{
public:
	void OnInitialize() override;
	void OnUpdate() override;
};

