#pragma once
#include <iostream>

class Player;

class PlayerAction
{
public:
	virtual void Start(Player* pPlayer) = 0;
	virtual void Update(Player* pPlayer, float deltatime) = 0;
	~PlayerAction() = default;
};

class PlayerAction_Idle : public PlayerAction
{
public:
	void Start(Player* pPlayer) override;
	void Update(Player* pPlayer, float deltatime) override;
	~PlayerAction_Idle() = default;
};

class PlayerAction_Moving : public PlayerAction
{
public:
	void Start(Player* pPlayer) override;
	void Update(Player* pPlayer, float deltatime) override;
	~PlayerAction_Moving() = default;
};

class PlayerAction_Jumping : public PlayerAction
{
public:
	void Start(Player* pPlayer) override;
	void Update(Player* pPlayer, float deltatime) override;
	~PlayerAction_Jumping() = default;
};

class PlayerAction_Falling : public PlayerAction
{
public:
	void Start(Player* pPlayer) override;
	void Update(Player* pPlayer, float deltatime) override;
	~PlayerAction_Falling() = default;
};

class PlayerAction_TakingDamage : public PlayerAction
{
public:
	void Start(Player* pPlayer) override;
	void Update(Player* pPlayer, float deltatime) override;
	~PlayerAction_TakingDamage() = default;
};

class PlayerAction_Dying : public PlayerAction
{
	float mTimer;
	float mProgress;
	bool mIsPlayed;
public:
	void Start(Player* pPlayer) override;
	void Update(Player* pPlayer, float deltatime) override;
	~PlayerAction_Dying() = default;
};

class PlayerAction_Dashing : public PlayerAction
{
	float mDuration;
public:
	void Start(Player* pPlayer) override;
	void Update(Player* pPlayer, float deltatime) override;
	~PlayerAction_Dashing() = default;
};

class PlayerAction_AFK : public PlayerAction
{
	bool isStopping;
public:
	void Start(Player* pPlayer) override;
	void Update(Player* pPlayer, float deltatime) override;
	~PlayerAction_AFK() = default;
};