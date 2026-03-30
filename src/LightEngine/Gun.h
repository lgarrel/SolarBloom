#pragma once
#include <SFML/Graphics.hpp>
#include "Weapon.h"
#define PI 3.1415926535

class Gun : public Weapon
{
	float mAngle = 0;

public:
	void OnInitialize() override;
	void OnUpdate() override;
	void FixedUpdate(float dt) override; 
	void Shoot() override;

};

