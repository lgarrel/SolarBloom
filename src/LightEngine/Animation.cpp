#include "Animation.h"
#include <iostream>
#include <fstream>

void Animation::LoadJsonData(const char* path)
{
	// Lire le fichier JSON
	std::ifstream inputFile(path);

	if (!inputFile.is_open()) 
	{
		std::cerr << "Erreur lors de l'ouverture du fichier JSON." << std::endl;
		return;
	}

	inputFile >> data;
	inputFile.close();
}

void Animation::LoadAnimationSingle(const char* name)
{
	mFinished = false;
	mCurrentAnimation = name;
	mTextureRects.clear();

	sf::Vector2i frameSize = { data["frame_size"]["width"], data["frame_size"]["height"] };

	int frameCount = data["animations"][name]["frames"];
	int frameIndex = data["animations"][name]["index"];
	int spaceIBT = data["frame_size"]["space"];

	for (int i = 0; i < frameCount; i++)
	{
		sf::Vector2i framePosition = { frameSize.x * i + spaceIBT * i, (frameSize.y * frameIndex) + 1 * frameIndex };
		sf::IntRect frame = sf::IntRect(framePosition, frameSize );

		mTextureRects.push_back(frame);
	}

	mMaxFrame = mTextureRects.size() - 1;
	mCurrentFrame = 0;
	mElapsedTime = 0.f;
	mLoop = data["animations"][name]["loop"];
}

void Animation::LoadAnimationByRow(const char* eltName)
{
	mFinished = false;
	mCurrentAnimation = eltName;
	mTextureRects.clear();

	sf::Vector2i frameSize = { data["frame_size"]["width"], data["frame_size"]["height"] };

	int frameCount = data["elements"][eltName]["frames"];
	int frameIndex = data["elements"][eltName]["index"];
	int spaceIBT = data["frame_size"]["space"];

	for (int i = 0; i < frameCount; i++)
	{
		sf::Vector2i framePosition = { frameSize.x * i + spaceIBT * i, frameSize.y * frameIndex };
		sf::IntRect frame = sf::IntRect(framePosition, frameSize);

		mTextureRects.push_back(frame);
	}

	mMaxFrame = mTextureRects.size() - 1;
	mCurrentFrame = 0;
	mElapsedTime = 0.f;
	mLoop = data["elements"][eltName]["loop"];
}

void Animation::LoadAnimationGrid(const char* name)
{
	mCurrentAnimation = name;
	mTextureRects.clear();

	sf::Vector2i frameSize = { data["frame_size"]["width"], data["frame_size"]["height"] };
	sf::Vector2i frameIndex = { data["elements"][name]["x"], data["elements"][name]["y"]}; 

	sf::Vector2i framePosition = { (frameSize.x + 1) * frameIndex.x, (frameSize.y + 1) * frameIndex.y };
	sf::IntRect frame = sf::IntRect(framePosition, frameSize);

	mTextureRects.push_back(frame);

	mMaxFrame = 0;
	mCurrentFrame = 0;
	mElapsedTime = 0.f;
	mLoop = false;
	mStatic = true;
}

void Animation::Update(float dt)
{
	if (mMaxFrame <= 0 || mStatic == true)
		return;

	mElapsedTime += dt;
	if (mElapsedTime >= mDuration) 
	{
		mElapsedTime = 0.f;
		if (mCurrentFrame < mMaxFrame) 
		{
			mCurrentFrame++;
		}
		else if (mLoop) 
		{
			mCurrentFrame = 0; 
		}
		else
		{
			mFinished = true;
		}
	}
}

const char* Animation::GetCurrentAnimation()
{
	return mCurrentAnimation;
}

int Animation::GetMaxFrame()
{
	return mMaxFrame;
}

int Animation::GetCurrentFrameIndex()
{
	return mCurrentFrame;
}

bool Animation::IsFinished()
{
	return mFinished;
}

sf::IntRect* Animation::GetCurrentFrame()
{
	if (mMaxFrame <= 0 && mStatic == false) 
		return nullptr;

	return &mTextureRects[mCurrentFrame];
}


