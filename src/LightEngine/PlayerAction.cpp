#include "PlayerAction.h"
#include "TestScene.h"
#include "Player.h"
#include "Weapon.h"

void PlayerAction_Idle::Start(Player* pPlayer)
{
}

void PlayerAction_Idle::Update(Player* pPlayer, float deltatime)
{

	if (pPlayer->mOnGround == false && pPlayer->mProgress >= pPlayer->mDelay)
	{
		pPlayer->TransitionTo(Player::Falling);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Joystick::isButtonPressed(0, 1)) // bouton X
	{
		pPlayer->TransitionTo(Player::Jumping);
	}

}


void PlayerAction_Moving::Start(Player* pPlayer)
{

}

void PlayerAction_Moving::Update(Player* pPlayer, float deltatime)
{

	float* speed = &(pPlayer->mSpeed);
	*speed += pPlayer->mParameters.mAcceleration * deltatime;
	if (*speed > pPlayer->mParameters.mMaxSpeed)
	{
		*speed = pPlayer->mParameters.mMaxSpeed;
	}

	if (pPlayer->mIsMoving == false)
		pPlayer->TransitionTo(Player::Idle);


	if (pPlayer->mOnGround == false && pPlayer->mProgress >= pPlayer->mDelay) 
	{
		pPlayer->TransitionTo(Player::Falling);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Joystick::isButtonPressed(0, 1))// bouton X 
	{
		pPlayer->TransitionTo(Player::Jumping);
	}
}



void PlayerAction_Jumping::Start(Player* pPlayer)
{
	pPlayer->mHitbox.face = Player::CollideWith::Nothing;
	pPlayer->SetGravity(true);

	pPlayer->mOnGround = false;

	pPlayer->mProgress = 0.f;

	pPlayer->mGravitySpeed = -std::sqrt(3 * GRAVITY_ACCELERATION * pPlayer->GetSize().y);
	pPlayer->GetScene<TestScene>()->GetAssetManager()->GetSound("PlayerJump")->play();
}

void PlayerAction_Jumping::Update(Player* pPlayer, float deltatime)
{

	if(pPlayer->mGravitySpeed == 0)
		pPlayer->mGravitySpeed = -std::sqrt(3 * GRAVITY_ACCELERATION * pPlayer->GetSize().y); 

	if (pPlayer->mIsMoving)
	{
		float* speed = &(pPlayer->mSpeed);
		*speed += pPlayer->mParameters.mAcceleration * deltatime;
		if (*speed > pPlayer->mParameters.mMaxSpeed)
		{
			*speed = pPlayer->mParameters.mMaxSpeed;
		}
	}

	if (pPlayer->mGravitySpeed >= 0 && pPlayer->mOnGround == false)
	{
		pPlayer->TransitionTo(Player::Falling);
	}
}



void PlayerAction_Falling::Start(Player* pPlayer)
{

}

void PlayerAction_Falling::Update(Player* pPlayer, float deltatime)
{

	bool isMoving = false;

	isMoving = pPlayer->mIsMoving;

	if (isMoving)
	{
		float* speed = &(pPlayer->mSpeed);
		*speed += pPlayer->mParameters.mAcceleration * deltatime;
		if (*speed > pPlayer->mParameters.mMaxSpeed)
		{
			*speed = pPlayer->mParameters.mMaxSpeed;
		}

	}

	if (pPlayer->mOnGround == true && isMoving == false)
	{
		pPlayer->GetScene<TestScene>()->GetAssetManager()->GetSound("Landing")->play();
		pPlayer->TransitionTo(Player::Idle);
	}
	else if (pPlayer->mOnGround == true && isMoving == true)
	{
		pPlayer->GetScene<TestScene>()->GetAssetManager()->GetSound("Landing")->play();
		pPlayer->TransitionTo(Player::Moving);
	}
}



void PlayerAction_TakingDamage::Start(Player* pPlayer)
{

	pPlayer->mOnGround = false;
	pPlayer->AddRemoveHP(-1);
	pPlayer->GetScene<TestScene>()->GetAssetManager()->GetSound("Hurt")->play();
}

void PlayerAction_TakingDamage::Update(Player* pPlayer, float deltatime)
{
	if (pPlayer->GetRatioHP() <= 0)
	{
		pPlayer->TransitionTo(Player::Dying);
	}

	pPlayer->TransitionTo(Player::Falling);
}



void PlayerAction_Dying::Start(Player* pPlayer)
{
	mTimer = 1.f;
	mProgress = 0.f;
	mIsPlayed = false;
	pPlayer->SetRigidBody(false);
	pPlayer->SetIsHitboxActive(false);
	pPlayer->SetGravity(false);
	pPlayer->SetSpeed(0);
	pPlayer->ChangeColor(sf::Color::Transparent);
}

void PlayerAction_Dying::Update(Player* pPlayer, float deltatime)
{

	if (pPlayer->GetScene<TestScene>()->GetAssetManager()->GetSound("Dead")->getStatus() == sf::Sound::Status::Stopped() && mIsPlayed == true)
	{
		pPlayer->GetScene<TestScene>()->GetAssetManager()->GetMusic("MainMusic")->play();
		PlayerParameter* pParam = &pPlayer->mParameters;

		pParam->mRespawnX = pPlayer->mParameters.mDefaultRespawnX; 
		pParam->mRespawnY = pPlayer->mParameters.mDefaultRespawnY;
		pPlayer->SetPosition(pParam->mRespawnX, pParam->mRespawnY);

		for (Weapon* w : pPlayer->GetAllWeapons())
		{
			w->SetCurrentAmmos(w->GetMaxAmmos());
		}

		pPlayer->TransitionTo(Player::Falling);

		pPlayer->SetRigidBody(true);
		pPlayer->SetIsHitboxActive(true);
		pPlayer->SetGravity(true);
		pPlayer->mIsDead = false;
		pPlayer->ChangeColor(sf::Color::White);
		pPlayer->mCurrentHP = pPlayer->mMaxHP;
	}

	if (mProgress >= mTimer && mIsPlayed == false)
	{
		pPlayer->GetScene<TestScene>()->GetAssetManager()->GetSound("Dead")->play();
		mProgress = 0.f;
		mIsPlayed = true;	
		pPlayer->GetScene<TestScene>()->GetAssetManager()->GetMusic("MainMusic")->stop();
	}
	else
	{
		mProgress += deltatime;
	}
}



void PlayerAction_Dashing::Start(Player* pPlayer)
{
	if (pPlayer->mSpeed > 0)
	{
		mDuration = 0.2f;
	}
	else
	{
		mDuration = 0.1f;
	}

	pPlayer->GetScene<TestScene>()->GetAssetManager()->GetSound("PlayerDash")->play(); 
}

void PlayerAction_Dashing::Update(Player* pPlayer, float deltatime)
{
	if (pPlayer->mParameters.mMaxSpeed >= pPlayer->mParameters.mDefaultMaxSpeed)
		pPlayer->mSpeed = 500.f;
	else
		pPlayer->mSpeed = 0.f;

	float* speedBoost = &(pPlayer->mSpeed);
	*speedBoost += pPlayer->mParameters.mAcceleration * deltatime * 50;
	if (*speedBoost > pPlayer->mParameters.mMaxSpeed * 15)
	{
		*speedBoost = pPlayer->mParameters.mMaxSpeed;
	}

	if (mDuration > 0)
	{
		if (pPlayer->mHitbox.face != Player::CollideWith::Left && pPlayer->mHitbox.face != Player::CollideWith::Right)
		{
			pPlayer->SetGravity(false);
			pPlayer->mOnGround = false;
		}
		else
			mDuration = 0.f;
	}
	else
	{
		pPlayer->SetGravity(true);

		*speedBoost = 0.f;

		pPlayer->mOnGround = false;
		pPlayer->TransitionTo(Player::Falling);
	}

	mDuration -= deltatime;
}

void PlayerAction_AFK::Start(Player* pPlayer)
{
	isStopping = false;
}

void PlayerAction_AFK::Update(Player* pPlayer, float deltatime)
{
	if (isStopping)
		pPlayer->TransitionTo(Player::Falling);
}
