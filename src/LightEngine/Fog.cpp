#include "Fog.h"
#include "TestScene.h"

void Fog::OnInitialize()
{
	SetKineticBody(false);
	Obstacle::OnInitialize();
	SetTagObstacle(TagObstacle::TFog);
	SetHitbox(GetSize().x, GetSize().y);
	SetRigidBody(false);
}

void Fog::OnCollision(Entity* collidedWith)
{
}

void Fog::OnUpdate()
{
}