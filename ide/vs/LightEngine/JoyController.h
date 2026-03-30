#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class JoyController
{
private:
	float x = sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::X);
	float y = sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::Y);
	unsigned int buttonCount = sf::Joystick::getButtonCount(0);
public:
	void Controller_OnUpdate();
};

