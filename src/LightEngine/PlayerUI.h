#pragma once

class Player;

class PlayerUI
{
protected:
	bool mDisplay = true;
	Player* pOwner;
	
public:
	virtual void UpdateUI() = 0; 
	void SetDisplay(bool value) { mDisplay = value; }
	void SetOwner(Player* pPlayer) { pOwner = pPlayer; }
};

