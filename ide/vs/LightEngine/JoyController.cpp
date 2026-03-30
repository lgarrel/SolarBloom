#include "JoyController.h"

void JoyController::Controller_OnUpdate()
{
	
	if (sf::Joystick::isConnected(0))
	{
		std::cout << "JoyStick Connecte" << std::endl;
	}
	if (sf::Joystick::isButtonPressed(0, 1))
	{
		/* TODO*/
	}

}