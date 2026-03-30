#include "Obstacle.h"
#include "TestScene.h"

void Obstacle::OnInitialize()
{
	player = GetScene<TestScene>()->GetPlayer();
	SetTag(TestScene::TObstacle);
}