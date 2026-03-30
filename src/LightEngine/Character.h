#pragma once
#include "PhysicalEntity.h"
#include "Health.h"


class Character : public PhysicalEntity, public Health
{
public:
	Character(int maxHP);
};

