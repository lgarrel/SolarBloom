#include "Bramble.h"
#include"TestScene.h"
#include "Animation.h"
#include "BrambleExplosion.h"

Bramble::Bramble() : Enemy(BRAMBLE_HP) {}

void Bramble::OnInitialize()
{
	SetKineticBody(false);
	SetRigidBody(true);
	Enemy::OnInitialize(); 
	SetTagEnemy(Enemy::TBramble);
	mIsDead = false;
	mProximityRadius = GetSize().x * 1.5f + GetSize().x / 2 + player->GetSize().x / 2;

	mExplosion = CreateEntity<BrambleExplosion>({ GetSize().x * 5, GetSize().y }, sf::Color::Red, 3);

	LoadAnimation();
}

void Bramble::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TAcid))
	{
		Explose();
	}
}

void Bramble::OnUpdate()
{
	if (mIsDead)
	{
		GetScene<TestScene>()->GetAssetManager()->GetSound("DeadMonster")->play();
		Destroy();
		return;
	}

	Enemy::OnUpdate();

	isPlayerInProximity = IsPlayerInProximity();
	if (isPlayerInProximity)
	{
		mExplosionActive = true;
	}

	if (mExplosionActive)
	{
		mExplosionTimer += GetDeltaTime();
	}

	if (mExplosionTimer >= mExplosionDelay)
	{
		ChangeAnimation("Death", "single");
		Explose();
	}
}

void Bramble::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Bramble.json");
	SetTexture("Bramble");
	mAnimations->LoadAnimationSingle("Idle");
}
void Bramble::Explose()
{
	mExplosion->ChangeAnimation("Dissipate", "byRow");
	mExplosion->SetPosition(GetPosition().x, GetPosition().y);

	SetHitbox(GetSize().x * 5, GetSize().y * 5);
	if (isPlayerInProximity)
	{
		player->AddRemoveHP(-1);
		player->TransitionTo(Player::TakingDamage);
	}
	AddRemoveHP(-1);
	mExplosionTimer = 0.f;
}

bool Bramble::IsPlayerInProximity()
{
	sf::Vector2f playerPosition = player->GetPosition();
	sf::Vector2f thornPosition = GetPosition();

	float distance = GetDistance(playerPosition, thornPosition);

	return distance <= mProximityRadius;
}