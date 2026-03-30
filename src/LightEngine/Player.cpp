#include "Gun.h"
#include "WeedKiller.h"
#include "Weapon.h"
#include "TestScene.h"
#include "Debug.h"
#include "PlayerAmmoBar.h"
#include "PlayerHealthBar.h"
#include "PlayerUI.h"
#include "Ally.h"
#include "Station.h"
#include "Enemy.h"
#include "Obstacle.h"
#include "PlayerAction.h"
#include "Animation.h"
#include "DashUI.h"

#include <iostream>

Player::Player() : Character(PLAYER_HP)
{
	PlayerHealthBar* pPlayerHB = new PlayerHealthBar();
	PlayerAmmoBar* pPlayerAB = new PlayerAmmoBar();
	DashUI* pDashUI = CreateEntity<DashUI>({ 25.f,50.f }, sf::Color::White, 7);

	mUI.push_back(pPlayerHB);
	mUI.push_back(pPlayerAB);
	mUI.push_back(pDashUI);

	for (PlayerUI* ui : mUI)
	{
		ui->SetOwner(this);
	}
}

void Player::BasicControls()
{
	mJoyX = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);

	mIsMoving = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || mJoyX > 25)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || mJoyX < -25)
		{
			mIsMoving = false;
			mSide = -1;
		}
		else
		{
			mIsMoving = true;
			mSide = 1;
		}
		mDirection.x = mSide;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || mJoyX < -25)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || mJoyX > 25)
		{
			mIsMoving = false;
			mSide = 1;

		}
		else
		{
			mIsMoving = true;
			mSide = -1;
		}
		mDirection.x = mSide;
	}

	UpdateAnimation();

	if (mIsMoving && mState != Falling)
		TransitionTo(Player::Moving);

	if (mIsMoving == false && mState != Dashing)
		mSpeed = 0.f;

}

void Player::InitStates()
{
	for (int i = 0; i < STATE_COUNT; i++)
	{
		for (int j = 0; j < STATE_COUNT; j++)
		{
			mTransitions[i][j] = false;
		}
	}

	////Idle, Moving,  Jumping,Dashing, Falling, TakingDmg, Dying
	//{ 0,	  1,	   1,	   1,	    1,		 1,			1 }, // Idle
	//{ 1,    0,       1,	   1,       1,       1,         1 }, // Moving
	//{ 0,    1,       0,	   1,       1,       1,         1 }, // Jumping
	//{ 1,    0,       0,	   0,       0,       0,         0 }, // Dashing
	//{ 1,    1,       0,	   1,       0,       1,         1 }, // Falling
	//{ 1,    0,       0,	   0,       0,       0,         1 }, // TakingDmg
	//{ 0,    0,       0,	   0,       0,       0,         0 }  // Dying

	SetTransition(Idle, Moving, true);
	SetTransition(Idle, Jumping, true);
	SetTransition(Idle, Dashing, true);
	SetTransition(Idle, Falling, true);
	SetTransition(Idle, TakingDamage, true);
	SetTransition(Idle, Dying, true);
	SetTransition(Idle, AFK, true);

	SetTransition(Moving, Idle, true);
	SetTransition(Moving, Jumping, true);
	SetTransition(Moving, Dashing, true);
	SetTransition(Moving, Falling, true);
	SetTransition(Moving, TakingDamage, true);
	SetTransition(Moving, Dying, true);
	SetTransition(Moving, AFK, true);

	SetTransition(Jumping, Dashing, true);
	SetTransition(Jumping, Falling, true);
	SetTransition(Jumping, TakingDamage, true);
	SetTransition(Jumping, Dying, true);
	SetTransition(Jumping, AFK, true);

	SetTransition(Dashing, Falling, true);
	SetTransition(Dashing, AFK, true);

	SetTransition(Falling, Idle, true);
	SetTransition(Falling, Moving, true);
	SetTransition(Falling, Dashing, true);
	SetTransition(Falling, TakingDamage, true);
	SetTransition(Falling, Dying, true);
	SetTransition(Falling, AFK, true);

	SetTransition(TakingDamage, Falling, true);
	SetTransition(TakingDamage, Dying, true);
	SetTransition(TakingDamage, AFK, true);

	SetTransition(Dying, Falling, true);

	SetTransition(AFK, Falling, true);


	mAction[Idle] = new PlayerAction_Idle();
	mAction[Moving] = new PlayerAction_Moving();
	mAction[Jumping] = new PlayerAction_Jumping();
	mAction[Falling] = new PlayerAction_Falling();
	mAction[TakingDamage] = new PlayerAction_TakingDamage();
	mAction[Dying] = new PlayerAction_Dying();
	mAction[Dashing] = new PlayerAction_Dashing();
	mAction[AFK] = new PlayerAction_AFK();
}

bool Player::TransitionTo(State newState)
{
	if (mTransitions[(int)mState][(int)newState])
	{
		mAction[(int)newState]->Start(this);
		mState = newState;

		return true;
	}

	return false;
}

void Player::OnInitialize()
{
	PhysicalEntity::OnInitialize();
	InitStates();

	SetTag((int)TestScene::TPlayer);

	Weapon* gun = CreateEntity<Gun>({ 20, 20 }, sf::Color::Transparent, 2);
	gun->SetOwner(this);

	Weapon* weedKiller = CreateEntity<WeedKiller>({ 20, 20 }, sf::Color::Transparent, 2);
	weedKiller->SetOwner(this);

	mWeapons.push_back(gun);
	mWeapons.push_back(weedKiller);

	LoadAnimation();
}

void Player::OnUpdate()
{
	mAction[mState]->Update(this, GetDeltaTime());

	if (mState != Jumping || mState != Falling)
	{
		if (mHitbox.face == CollideWith::Nothing)
		{
			mOnGround = false;
		}
	}

	if (mIsDead)
	{
		TransitionTo(Player::Dying);
		return;
	}

	PhysicalEntity::OnUpdate();

	if (mState != AFK)
		BasicControls();

	for (PlayerUI* ui : mUI)
	{
		ui->UpdateUI();
	}

	int fpsCounter = (int)(1.f / GetDeltaTime());

	sf::Vector2f camPos = GetScene<TestScene>()->GetCam().GetView()->getCenter();

	Debug::DrawText(camPos.x + 500, camPos.y - 340, "FPS : " + std::to_string(fpsCounter), sf::Color::White);

	if (mProgressDashReload <= 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Joystick::isButtonPressed(0, 5))
		{
			TransitionTo(Dashing);
			mProgressDashReload = mParameters.mDashReloadTime;
		}
	}
	else
	{
		mProgressDashReload -= GetDeltaTime();
	}

	SwapManager();

	sf::Vector2f pos = GetPosition();

	for (Weapon* w : mWeapons)
	{
		w->SetPosition(pos.x + mSide * mHitbox.size.x * 0.5f, pos.y);

		if (w->IsTag(GetScene<TestScene>()->TGun) && w->GetIsEquiped() == true && mState != AFK) 
		{
			sf::Vector2f gunPos = w->GetPosition();
			sf::Vector2f gunDir = w->GetDirection();

			Debug::DrawLine(gunPos.x, gunPos.y, gunPos.x + gunDir.x * 100, gunPos.y + gunDir.y * 100, sf::Color::Red);
		}
	}

	Respawn(mParameters.mRespawnX, mParameters.mRespawnY);
}

void Player::Respawn(int x, int y)
{
	if (GetPosition().y > 900)
	{
		TransitionTo(Player::TakingDamage);
		GetScene<TestScene>()->GetAssetManager()->GetSound("Falling")->play();

		if (GetRatioHP() > 0 || mState != AFK)
			SetPosition(x, y);


		if (mRespawnStation == nullptr)
			return;

		mRespawnStation->ChangeAnimation("Used", "single");
	}
}

void Player::OnCollision(Entity* other)
{
	Ally* ally = dynamic_cast<Ally*>(other);
	Enemy* enemy = dynamic_cast<Enemy*>(other);
	Obstacle* obstacle = dynamic_cast<Obstacle*>(other);

	if (ally)
	{
		if (ally->IsTagAlly(Ally::TStation))
		{
			mParameters.mRespawnX = other->GetPosition().x;
			mParameters.mRespawnY = other->GetPosition().y - other->GetSize().y / 2;
			mRespawnStation = dynamic_cast<Station*>(ally);

			sf::Sound* cpSfx = GetScene<TestScene>()->GetAssetManager()->GetSound("Checkpoint");

			if (cpSfx->getStatus() == sf::Sound::Status::Stopped)
			{
				cpSfx->play();
			}

			for (Weapon* weapon : mWeapons)
			{
				if (weapon->IsTag(TestScene::TWeedKiller))
				{
					weapon->SetCurrentAmmos(weapon->GetMaxAmmos());
					break;
				}
			}
		}
		if (ally->IsTagAlly(Ally::TVineG))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Joystick::isButtonPressed(0, 1))// bouton X
			{
				mGravitySpeed = -std::sqrt(9.81 * 50.f * GetSize().y);
			}
		}

	}

	if (!other->IsTag(TestScene::TPlatform) && !ally && !enemy && !obstacle)
		return;

	if (ally)
	{
		if (!ally->IsTagAlly(Ally::TNenuphloatG))
			return;
	}

	if (enemy)
	{
		if (!enemy->IsTagEnemy(Enemy::TFongusR) && !enemy->IsTagEnemy(Enemy::TBramble))
			return;
	}

	if (obstacle)
	{
		if (!obstacle->IsTagObstacle(Obstacle::TBridge) && !obstacle->IsTagObstacle(Obstacle::TRootG) && !obstacle->IsTagObstacle(Obstacle::TWall))
			return;
	}

	switch (mHitbox.face)
	{
	case CollideWith::Bottom:
		mGravitySpeed = 0.f;
		mProgress = 0.f;
		mOnGround = true;

		break;

	case CollideWith::Top:
		if (mState == Jumping)
		{
			mGravitySpeed = 1.f;
			mOnGround = false;
			TransitionTo(Falling);
			GetScene<TestScene>()->GetAssetManager()->GetSound("Bonk")->play();
		}
		break;

	case CollideWith::Left:
		mOnGround = false;
		break;

	case CollideWith::Right:
		mOnGround = false;
		break;

	default:
		std::cout << "Bug\n";
		break;
	}
}

void Player::OnDestroy()
{
	GetScene<TestScene>()->GetCam().SetOwner(nullptr);

	for (Weapon* w : mWeapons)
	{
		w->SetOwner(nullptr);
		w->Destroy();
	}

	mWeapons.clear();

	for (PlayerUI* ui : mUI)
	{
		delete ui;
		ui = nullptr;
	}

	mUI.clear();
}

void Player::FixedUpdate(float dt)
{
	Entity::FixedUpdate(dt);
	PhysicalEntity::FixedUpdate(dt);
}

void Player::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Hydro.json");
	SetTexture("Hydro");
	mAnimations->LoadAnimationSingle("IdleRight");
}

void Player::UpdateAnimation()
{
	Weapon* weapon = GetCurrentEquipedWeapon();

	if (weapon->GetTag() == TestScene::Tag::TGun)
	{
		UpdateAnimationBlue();
	}
	else
	{
		UpdateAnimationGreen();
	}
}

void Player::UpdateAnimationBlue()
{
	const char* currentAnim = mAnimations->GetCurrentAnimation();

	if (mIsMoving)
	{
		if (mSide == 1 && currentAnim != "WalkRightBlue")
		{
			ChangeAnimation("WalkRightBlue", "single");
		}
		else if (mSide == -1 && currentAnim != "WalkLeftBlue")
		{
			ChangeAnimation("WalkLeftBlue", "single");
		}
	}
	else
	{
		if (mSide == 1 && currentAnim != "IdleRightBlue")
		{
			ChangeAnimation("IdleRightBlue", "single");
		}
		else if (mSide == -1 && currentAnim != "IdleLeftBlue")
		{
			ChangeAnimation("IdleLeftBlue", "single");
		}
	}
}

void Player::UpdateAnimationGreen()
{
	const char* currentAnim = mAnimations->GetCurrentAnimation();

	if (mIsMoving)
	{
		if (mSide == 1 && currentAnim != "WalkRight")
		{
			ChangeAnimation("WalkRight", "single");
		}
		else if (mSide == -1 && currentAnim != "WalkLeft")
		{
			ChangeAnimation("WalkLeft", "single");
		}
	}
	else
	{
		if (mSide == 1 && currentAnim != "IdleRight")
		{
			ChangeAnimation("IdleRight", "single");
		}
		else if (mSide == -1 && currentAnim != "IdleLeft")
		{
			ChangeAnimation("IdleLeft", "single");
		}
	}
}

void Player::SwapManager()
{
	if (mDelayToSwap >= 0.5f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) || sf::Joystick::isButtonPressed(0, 3))
		{
			SwapWeapon();
		}
	}
	else
	{
		mDelayToSwap += GetDeltaTime();
	}
}

void Player::SwapWeapon()
{
	mDelayToSwap = 0.f;

	auto it = mWeapons.begin();

	for (it; it < mWeapons.end(); ++it)
	{
		if ((*it)->GetIsEquiped())
		{
			(*it)->SetIsEquiped(false);

			if (it == mWeapons.end() - 1)
			{
				it = mWeapons.begin();

				(*it)->SetIsEquiped(true);
			}
			else
			{
				(*(it + 1))->SetIsEquiped(true);
			}
			break;
		}
	}
}

Weapon* Player::GetCurrentEquipedWeapon()
{
	for (Weapon* w : mWeapons)
	{
		if (w->GetIsEquiped() == true)
			return w;
	}
}
