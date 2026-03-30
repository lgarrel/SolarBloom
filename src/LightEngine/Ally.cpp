#include "Ally.h"
#include "TestScene.h"

void Ally::OnInitialize()
{
	PhysicalEntity::OnInitialize();
	SetTag(TestScene::TAlly);
	SetIsHitboxActive(false);
}

void Ally::OnUpdate()
{
	PhysicalEntity::OnUpdate();
}
