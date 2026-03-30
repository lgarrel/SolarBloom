#pragma once
#include "Scene.h"
#include "Camera.h"
#include "GameManager.h"
#include "AssetManager.h"

class BG;
class Logo;
class PhysicalEntity;
class Player;

class TestScene : public Scene
{
	Logo* pLogo;
	BG* pBG;
public:
	enum Tag
	{
		TPlayer,
		TPlatform,
		TGun,
		TWeedKiller,
		TWater,
		TAcid,
		TAlly,
		TEnemy,
		TObstacle,
		TEnd,
		TLogo,
		TBG,

		Count
	};

	static constexpr int TAG_COUNT = static_cast<int>(Count); 
private:
	Camera mCam;
	AssetManager* assetManager = AssetManager::Get();

	Player* pEntity1;

	int mInteractions[TAG_COUNT][TAG_COUNT]; 

	//Volume
	float mDelayToChangeVolume = 0.25f;
	float mProgressToChangeVolume = 0.f; 
	float mVolume = 0.5f;
	bool isStopSound = false;
private:
	void InitTransitions();
	void SetInteractionWith(Tag tag1, Tag tag2, bool value) { mInteractions[(int)tag1][(int)tag2] = value; mInteractions[(int)tag2][(int)tag1] = value; }
	void AddRemoveVolume(float value);
public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void UpdateCamera();
	Camera& GetCam() { return mCam; }

	Player* GetPlayer() { return pEntity1; }
	AssetManager* GetAssetManager() { return assetManager; }
	bool IsAllowedToCollide(int tag1, int tag2);

	void InitSounds();
	void InitTextures();
	void InitAssets();

	void SoundManager();
	void UpdateVolume();
	void StopSound(); 
};

