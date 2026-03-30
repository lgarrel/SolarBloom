#pragma once

#include <list>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

constexpr auto FIXED_DT = 0.01667f;

class Entity;
class Scene;
class Debug;
class Camera;

namespace sf 
{
	class RenderWindow;
	class Event;
}

class GameManager
{
	std::list<Entity*> mEntities;
	std::list<Entity*> mEntitiesToDestroy;
	std::list<Entity*> mEntitiesToAdd;

	sf::RenderWindow* mpWindow;
	sf::Font mFont;

	Scene* mpScene;

	float mDeltaTime;
	float mAccumulatedDt = 0.f;

	int mWindowWidth;
	int mWindowHeight;

	sf::Color mClearColor;

private:
	GameManager();

	void Run();
	
	void HandleInput();
	void Update();
	void FixedUpdate();
	void Draw();

	void SetDeltaTime(float deltaTime) { mDeltaTime = deltaTime; }

public:
	~GameManager();
	static GameManager* Get();

	void CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60, sf::Color clearColor = sf::Color::Black);

	template<typename T>
	void LaunchScene();

	float GetDeltaTime() const { return mDeltaTime; }
	Scene* GetScene() const { return mpScene; }
	sf::Font& GetFont() { return mFont; };
	sf::RenderWindow* GetWindow() const { return mpWindow; }

	void SetCamera(const Camera& camera);

	friend Debug;
	friend Scene;
};

#include "GameManager.inl"