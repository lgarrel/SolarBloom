#include "Platform.h"
#include "TestScene.h"
#include "Animation.h"
#include <iostream>

void Platform::OnInitialize()
{
	PhysicalEntity::OnInitialize();
	mKineticBody = false;
	SetTag((int)TestScene::TPlatform);

	SetTexture("Terrain");
	LoadAnimation();
}

void Platform::OnUpdate()
{
	if(mHitbox.hasHitbox)
		PhysicalEntity::OnUpdate();
}

void Platform::OnCollision(Entity* other)
{
}

void Platform::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Terrain.json");
}
