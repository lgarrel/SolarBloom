
#include <SFML/Graphics.hpp>
#include <iostream>


#include "GameManager.h"
#include "SampleScene.h"
#include "TestScene.h"

#include <cstdlib>
#include <crtdbg.h>

int main() 
{
    GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "TestScene", 60, sf::Color(0, 220, 255, 255));
	
	pInstance->LaunchScene<TestScene>();

	return 0;
}