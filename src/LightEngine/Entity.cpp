#include "Entity.h"

#include "GameManager.h"
#include "Utils.h"
#include "Debug.h"
#include "TestScene.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>
#include "Animation.h"
#include "AssetManager.h"

void Entity::Initialize(sf::Vector2f size, const sf::Color& color, int mDrawPriority)
{
	mDirection = sf::Vector2f(0.0f, 0.0f);

	mShape.setOrigin(0.f, 0.f);
	mShape.setSize(size);
	mShape.setFillColor(color);
	SetHitbox(size.x, size.y);
	drawPriority = mDrawPriority;
	mTarget.isSet = false;

	mAnimations = new Animation();

	OnInitialize();
}

void Entity::Repulse(Entity* other) 
{
	sf::Vector2f distance = GetPosition(0.5f, 0.5f) - other->GetPosition(0.5f, 0.5f);

	float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);
	float length = std::sqrt(sqrLength);
	float overlap = 0.f;
	sf::Vector2f normal(0.f, 0.f);

	sf::Vector2f halfSize1 = GetAABBSize() * 0.5f;
	sf::Vector2f halfSize2 = other->GetAABBSize() * 0.5f;

	sf::Vector2f absDistance = { std::abs(distance.x), std::abs(distance.y) };
	sf::Vector2f totalSize = halfSize1 + halfSize2;

	float overlapX = totalSize.x - absDistance.x;
	float overlapY = totalSize.y - absDistance.y;

	if (overlapX < overlapY)
	{
		overlap = overlapX * 0.5f;
		normal = { (distance.x > 0 ? -1.0f : 1.0f), 0.0f };
	}
	else
	{
		overlap = overlapY * 0.5f;
		normal = { 0.0f, (distance.y > 0 ? -1.0f : 1.0f) };
	}

	if (overlap < 0.001f)
		overlap = 0.f;

	if (!mKineticBody)
	{
		overlap = 0.f;
	}
	else if (mKineticBody && !other->mKineticBody)
	{
		overlap *= 2.f;
	}

	sf::Vector2f translation = overlap * normal;

	sf::Vector2f position1 = GetPosition(0.5f, 0.5f) - translation;
	sf::Vector2f position2 = other->GetPosition(0.5f, 0.5f) + translation;

	if (mKineticBody)
		SetPosition(position1.x, position1.y, 0.5f, 0.5f);

	if (other->mKineticBody)
		other->SetPosition(position2.x, position2.y, 0.5f, 0.5f);
}

bool Entity::IsColliding(Entity* other)
{
	//If the collision between 2 entities isn't allowed, Skip
	if (GetScene<TestScene>()->IsAllowedToCollide(this->mTag, other->mTag) == false)
	{
		return false;
	}

	AABBCollider& hb = mHitbox;
	AABBCollider& otherHb = *(other->GetHitbox()); 

	if (!hb.isActive && !otherHb.isActive)
		return false;

	sf::Vector2f pos = GetPosition();
	sf::Vector2f otherPos = other->GetPosition();

	sf::Vector2f centerOfHB = { pos.x + hb.offsetX, pos.y + hb.offsetY }; 
	sf::Vector2f centerOfOtherHB = { otherPos.x + otherHb.offsetX, otherPos.y + otherHb.offsetY }; 

	float radiusBasedOndiagonalHB = GetDistance(centerOfHB, { hb.xMin, hb.yMin }); 
	float radiusBasedOndiagonalOtherHB = GetDistance(centerOfOtherHB, { otherHb.xMin, otherHb.yMin });  

	float distanceBetweenEntities = GetDistance(pos, otherPos);

	//If the entities are too far to each others, Skip
	if (distanceBetweenEntities > radiusBasedOndiagonalHB + radiusBasedOndiagonalOtherHB)
	{
		hb.face = CollideWith::Nothing; 
		otherHb.face = CollideWith::Nothing; 
		return false;
	}

	//If One of the entities has no hitbox, Skip
	if (hb.isActive == false || otherHb.isActive == false)
	{
		hb.face = CollideWith::Nothing;
		otherHb.face = CollideWith::Nothing;
		return false;
	}

	float hbWidth = abs(hb.xMax - hb.xMin); 
	float hbHeight = abs(hb.yMax - hb.yMin); 

	float otherHBWidth = abs(otherHb.xMax - otherHb.xMin); 
	float otherHBHeight = abs(otherHb.yMax - otherHb.yMin); 

	if (hbWidth <= 0 || hbHeight <= 0 || otherHBWidth <= 0 || otherHBHeight <= 0)
	{
		return false; 
	} 

	if (hb.xMax >= otherHb.xMin && hb.xMin <= otherHb.xMax)
	{
		if(hb.yMax >= otherHb.yMin && hb.yMin <= otherHb.yMax)
		{
			//Face Detection

			float overlapX = 0;
			float overlapY = 0;

			sf::Vector2f distBetweenCentersXY = { abs( pos.x + hb.offsetX - otherPos.x - otherHb.offsetX) , abs( pos.y + hb.offsetY - otherPos.y - otherHb.offsetY) }; 

			float halfWidth = hbWidth * 0.5f; 
			float halfHeight = hbHeight * 0.5f; 

			overlapX = hbWidth * 0.5f + otherHBWidth * 0.5f - distBetweenCentersXY.x;
			overlapY = hbHeight * 0.5f + otherHBHeight * 0.5f - distBetweenCentersXY.y;

			if (overlapX > overlapY)
			{
				if (hb.yMax < otherHb.yMax)
				{
					hb.face = CollideWith::Bottom;
					otherHb.face = CollideWith::Top;
				}
				else
				{
					hb.face = CollideWith::Top;
					otherHb.face = CollideWith::Bottom;
				}
			}
			else
			{
				if (hb.xMax < otherHb.xMax)
				{
					hb.face = CollideWith::Right;
					otherHb.face = CollideWith::Left;
				}
				else
				{
					hb.face = CollideWith::Left;
					otherHb.face = CollideWith::Right;
				}
			}

			return true;
		}
	}

	hb.face = CollideWith::Nothing;
	otherHb.face = CollideWith::Nothing;
	return false;
}

bool Entity::IsInside(float x, float y) const
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	float dx = x - position.x;
	float dy = y - position.y;

	sf::Vector2f size = mShape.getSize();

	return (dx * dx + dy * dy) < (size.x * size.y);
}

void Entity::UpdateHitBox()
{
	if (mHitbox.isActive == false)
		return;

	sf::Vector2f pos = GetPosition();

	AABBCollider h = mHitbox;

	float width = (h.xMax - h.xMin);
	float height = (h.yMax - h.yMin);

	if (width <= 0 || height <= 0)
	{
		return;
	}

	mHitbox.xMin = pos.x - width * 0.5f + mHitbox.offsetX;
	mHitbox.yMin = pos.y - height * 0.5f + mHitbox.offsetY;

	mHitbox.xMax = pos.x + width * 0.5f + mHitbox.offsetX;
	mHitbox.yMax = pos.y + height * 0.5f + mHitbox.offsetY;

	if(mHitbox.isDisplayed)
		Debug::DrawRectangle(mHitbox.xMin, mHitbox.yMin, width, height, sf::Color::Blue);
}

void Entity::SetHitbox(float width, float height, float ratioX, float ratioY)
{
	if (width < 0 || height < 0)
	{
		std::cout << "Impossible to set hitbox !\n";
		return;
	}

	mHitbox.size = { width, height };

	mHitbox.xMin = -width * ratioX;
	mHitbox.yMin = -height * ratioX;
	mHitbox.xMax = width * ratioY;
	mHitbox.yMax = height * ratioY;
}

void Entity::SetHitboxOffset(float offsetX, float offsetY)
{
	mHitbox.offsetX = offsetX;
	mHitbox.offsetY = offsetY;
}

void Entity::SetTexture(const char* name)
{
	AssetManager* assetManager = AssetManager::Get();
	mTexture = assetManager->GetTexture(name);
}

void Entity::UpdateFrame(float dt)
{
	if (mTexture == nullptr)
		return;

	mAnimations->Update(dt);
	sf::IntRect* frame = mAnimations->GetCurrentFrame();
	
	if (frame == nullptr)
	{
		//std::cout << "pas de frame trouve" << std::endl;
		return;
	}

	mShape.setTexture(mTexture);
	mShape.setTextureRect(*frame);
}

void Entity::ChangeColor(sf::Color newColor)
{
	mShape.setFillColor(newColor);
}

float Entity::GetDistance(sf::Vector2f e1, sf::Vector2f e2)
{
	return sqrt( pow(e2.x - e1.x, 2) + pow(e2.y - e1.y, 2) );
}

void Entity::Destroy()
{
	mToDestroy = true;

	OnDestroy();
}

void Entity::SetPosition(float x, float y, float ratioX, float ratioY)
{
	sf::Vector2f size = mShape.getSize();

	x -= size.x * ratioX;
	y -= size.y * ratioY;

	mShape.setPosition(x, y);

	//#TODO Optimise
	if (mTarget.isSet) 
	{
		sf::Vector2f position = GetPosition(0.5f, 0.5f);
		mTarget.distance = Utils::GetDistance(position.x, position.y, mTarget.position.x, mTarget.position.y);
		GoToDirection(mTarget.position.x, mTarget.position.y);
		mTarget.isSet = true;
	}
}

void Entity::SetHitboxPosition(sf::Vector2f)
{
	sf::Vector2f pos = GetHitboxPosition();

	mHitbox.xMin = pos.x - mHitbox.size.x * 0.5f;
	mHitbox.yMin = pos.y - mHitbox.size.y * 0.5;
	mHitbox.xMax = pos.x - mHitbox.size.x * 0.5f;
	mHitbox.yMax = pos.y - mHitbox.size.y * 0.5f;
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	sf::Vector2f size = mShape.getSize();
	sf::Vector2f position = mShape.getPosition();

	position.x += size.x * ratioX;
	position.y += size.y * ratioY;

	return position;
}

sf::Vector2f Entity::GetHitboxPosition(float ratioX, float ratioY) const
{
	sf::Vector2f size = mHitbox.size;
	sf::Vector2f position = GetPosition();

	position.x += size.x * ratioX;
	position.y += size.y * ratioY;

	return position;
}

bool Entity::GoToDirection(int x, int y, float speed)
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);
	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);
	
	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;

	SetDirection(direction.x, direction.y, speed);

	return true;
}

bool Entity::GoToPosition(int x, int y, float speed)
{
	if (GoToDirection(x, y, speed) == false)
		return false;

	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	mTarget.position = { x, y };
	mTarget.distance = Utils::GetDistance(position.x, position.y, x, y);
	mTarget.isSet = true;

	return true;
}

void Entity::SetDirection(float x, float y, float speed)
{
	if (speed > 0)
		mSpeed = speed;

	mDirection = sf::Vector2f(x, y);
	mTarget.isSet = false;
}

sf::Vector2f Entity::GetSize() const
{
	return mShape.getSize();
}

sf::Vector2f Entity::GetAABBSize() const
{
	return mHitbox.size;
}

void Entity::LoadAnimation()
{
	//Faire un LoadJsonData et un LoadAnimation en fonction de la struct
}

void Entity::ChangeAnimation(const char* name, const char* type)
{
	if (type == "single")
	{
		mAnimations->LoadAnimationSingle(name);
	}
	else if (type == "byRow")
	{
		mAnimations->LoadAnimationByRow(name);
	}
}

void Entity::FixedUpdate(float dt)
{
	float distance = dt * mSpeed;
	sf::Vector2f translation = distance * mDirection;
	mShape.move(translation);

	if (mTarget.isSet)
	{
		float x1 = GetPosition(0.5f, 0.5f).x;
		float y1 = GetPosition(0.5f, 0.5f).y;

		float x2 = x1 + mDirection.x * mTarget.distance;
		float y2 = y1 + mDirection.y * mTarget.distance;

		Debug::DrawLine(x1, y1, x2, y2, sf::Color::Cyan);

		Debug::DrawCircle(mTarget.position.x, mTarget.position.y, 5.f, sf::Color::Magenta);

		mTarget.distance -= distance;

		if (mTarget.distance <= 0.f)
		{
			SetPosition(mTarget.position.x, mTarget.position.y, 0.5f, 0.5f);
			mDirection = sf::Vector2f(0.f, 0.f);
			mTarget.isSet = false;
		}
	}
}

void Entity::Update()
{
	float dt = GetDeltaTime();

	UpdateFrame(dt);
	UpdateHitBox();
	OnUpdate();
}

Scene* Entity::GetScene() const
{
	return GameManager::Get()->GetScene();
}

float Entity::GetDeltaTime() const
{
	return GameManager::Get()->GetDeltaTime();
}