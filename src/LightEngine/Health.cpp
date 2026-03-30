#include "Health.h"

Health::Health(int maxHP)
{
	mMaxHP = maxHP;
	mCurrentHP = maxHP;
	mIsDead = false;
}

void Health::AddRemoveHP(int value)
{
	mCurrentHP += value;

	if (mCurrentHP > mMaxHP)
		mCurrentHP = mMaxHP;

	if (mCurrentHP <= 0)
	{
		mCurrentHP = 0;
		mIsDead = true;
	}
	else
		mIsDead = false;
}

void Health::SetCurrentHP(int value)
{
	mCurrentHP = value;

	if (mCurrentHP > mMaxHP)
		mCurrentHP = mMaxHP;

	if (mCurrentHP <= 0)
	{
		mCurrentHP = 0;
		mIsDead = true;
	}
	else
		mIsDead = false;
}
