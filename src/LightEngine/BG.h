#pragma once
#include "Entity.h"

class BG : public Entity
{
public:
	void OnInitialize() override;
	void OnUpdate() override;
};

