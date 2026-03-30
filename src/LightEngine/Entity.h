#pragma once

#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf 
{
	class Shape;
    class Color;
}

class Scene;
class Animation;

class Entity
{
	struct AABBCollider
	{
		bool isDisplayed = false;
		bool hasHitbox = true;
		int face = 0;

		bool isActive = true;

		float xMin, yMin;
		float xMax, yMax;

		float offsetX = 0.f, offsetY = 0.f;

		sf::Vector2f size;
	};

    struct Target 
    {
		sf::Vector2i position;
        float distance;
		bool isSet;
    };

protected:
	sf::RectangleShape mShape;
    sf::Vector2f mDirection;
	AABBCollider mHitbox;
	Target mTarget;
	Animation* mAnimations;
	sf::Texture* mTexture;
    float mSpeed = 0.f;
    bool mToDestroy = false;
    int mTag = -1;
	bool mRigidBody = false;
	bool mKineticBody;

	int drawPriority = 0;

public:
	enum CollideWith
	{
		Nothing,
		Left,
		Top,
		Right,
		Bottom,
	};

	bool GoToDirection(int x, int y, float speed = -1.f);
    bool GoToPosition(int x, int y, float speed = -1.f);
    void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
	sf::Vector2f GetDirection() { return mDirection; }
	void SetDirection(float x, float y, float speed = -1.f);
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetTag(int tag) { mTag = tag; }
	sf::Vector2f GetSize() const;
	sf::Vector2f GetAABBSize() const;
	void SetRigidBody(bool isRigitBody) { mRigidBody = isRigitBody; }
	bool IsRigidBody() const { return mRigidBody; }
	void SetKineticBody(bool value) { mKineticBody = value; }
	bool IsKineticBody() { return mKineticBody; }

	void SetHitboxPosition(sf::Vector2f);
    sf::Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const;
	sf::Vector2f GetHitboxPosition(float ratioX = 0.5f, float ratioY = 0.5f) const;
	sf::RectangleShape* GetShape() { return &mShape; }

	bool IsTag(int tag) const { return mTag == tag; }
    bool IsColliding(Entity* other);
	bool IsInside(float x, float y) const;

	//Changes
	AABBCollider* GetHitbox() { return &mHitbox; }
	void UpdateHitBox();
	void SetHitbox(float width, float height, float ratioX = 0.5f, float ratioY = 0.5f);
	void SetHitboxOffset(float offsetX, float offsetY);
	void SetIsHitboxActive(bool result = true) { mHitbox.isActive = result; }
	void SetTexture(const char* name);
	void UpdateFrame(float dt);
	void ChangeColor(sf::Color newColor);
	float GetDistance(sf::Vector2f e1, sf::Vector2f e2);

	virtual void LoadAnimation();
	void ChangeAnimation(const char* name, const char* type);
	Animation* GetAnimations() { return mAnimations; }

    void Destroy();
	bool ToDestroy() const { return mToDestroy; }
	
	template<typename T>
	T* GetScene() const;

    Scene* GetScene() const;
	float GetDeltaTime() const;

    template<typename T>
	T* CreateEntity(sf::Vector2f size, const sf::Color& color, int mDrawPriority);

protected:
    Entity() = default;
    ~Entity() = default;

    virtual void OnUpdate() {};
    virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};
	virtual void OnDestroy() {};
	virtual void FixedUpdate(float dt);

private:
    void Update();
	void Initialize(sf::Vector2f size, const sf::Color& color, int mDrawPriority);
	void Repulse(Entity* other);

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"