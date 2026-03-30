#pragma once

class Health
{
protected:
	int mMaxHP;
	int mCurrentHP;

	bool mIsDead;
public:
	Health(int maxHP);
	
	void AddRemoveHP(int value);
	void SetCurrentHP(int value);

	float GetRatioHP() { return (float)mCurrentHP / (float)mMaxHP; }

	int GetMaxHP() { return mMaxHP; }
	int GetCurrentHP() { return mCurrentHP; }
	bool IsDead() { return mIsDead; }
};

