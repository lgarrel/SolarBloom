#pragma once
#include "PhysicalEntity.h"
#include "Player.h"

class Obstacle : public PhysicalEntity
{
public:
	enum TagObstacle
	{
		TBridge,
		TRootG,
		TRootR,
		TFog,
		TWall,
	};

	Player* player;

	int mTagObstacle = -1;

	virtual void OnInitialize();

	void SetTagObstacle(int tagObstacle) { mTagObstacle = tagObstacle; }
	bool IsTagObstacle(int tagObstacle) const { return mTagObstacle == tagObstacle; }
};