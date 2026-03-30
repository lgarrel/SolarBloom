#pragma once
#include <SFML/Graphics.hpp>

#include <map>
#include <vector>

#include "json.hpp"

using json = nlohmann::json;

class Animation
{
	std::vector<sf::IntRect> mTextureRects;
	json data;

	int mMaxFrame = 0;
	int mCurrentFrame = 0;
	float mDuration = 0.25f;
	float mElapsedTime = 0.f;
	bool mLoop;
	bool mFinished = false;
	bool mStatic = false;
	const char* mCurrentAnimation;

public:
	void LoadJsonData(const char* path);
	void LoadAnimationSingle(const char* name);
	void LoadAnimationByRow(const char* name);
	void LoadAnimationGrid(const char* name);
	void Update(float dt);

	void SetLoop(bool value) { mLoop = value; }

	const char* GetCurrentAnimation();
	int GetMaxFrame();
	int GetCurrentFrameIndex();
	bool IsFinished();

	sf::IntRect* GetCurrentFrame();
};

