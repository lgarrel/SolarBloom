#include "TestScene.h"
#include "PhysicalEntity.h"
#include "Player.h"
#include "Platform.h"
#include "Vine.h"
#include "Station.h"
#include "Bulb.h"
#include "Nenuphloat.h"
#include "Thorn.h"
#include "Fongus.h"
#include "Ivy.h"
#include "Bramble.h"
#include "Bridge.h"
#include "Wall.h"
#include "Root.h"
#include "Fog.h"
#include "End.h"
#include "Logo.h"
#include "BG.h"

#include "DummyEntity.h"
#include "Animation.h"
#include "Debug.h"
#include <iostream>

#include <SFML/Graphics.hpp>

#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

void TestScene::OnInitialize()
{
	InitAssets();
	InitTransitions();

	int height = GetWindowHeight();
	int width = GetWindowWidth();

	mCam.Resize(width, height);

	pEntity1 = CreateEntity<Player>({ 75.f, 75.f }, sf::Color::White, 2);
	pEntity1->SetPosition(1000, 750);
	pEntity1->SetRigidBody(true);
	pEntity1->SetIsHitboxActive(true);
	pEntity1->SetGravity(true);
	pEntity1->SetKineticBody(true);

	pLogo = CreateEntity<Logo>({ 1280, 720 }, sf::Color::White, 6);
	pBG = CreateEntity<BG>({ 1280, 720 }, sf::Color::White, 1); 

	mCam.SetOwner(pEntity1);
	mCam.SetFocus(true);

	std::string filepath = "../../../res/map.txt";
	std::ifstream inputFile(filepath);

	if (!std::filesystem::exists(filepath)) {
		std::cerr << "Erreur : Le fichier n'existe pas a l'emplacement : " << filepath << std::endl;
	}

	if (!inputFile) {
		std::cerr << "Erreur : Impossible d'ouvrir " << filepath << std::endl;
	}

	std::vector<std::string> map;

	std::string line;
	while (std::getline(inputFile, line)) {
		map.push_back(line);
	}

	inputFile.close();
	const sf::Vector2f MOB_SIZE = { 50,50 };
	const sf::Vector2f BLOCK_SIZE = { 100, 50 };
	int startX = width / 2 - 250; 
	int startY = height / 2 - 200;

	/*
	Map Légende :

	Special :
	H : End Level
	Player :			2

	Platefrom :
	X : Land2			4
	L : BorderLand1		4
	l : CornerLand5		4
	C : CornerLand3		4
	c : CornerLand4		4
	E : EdgeLand1		4
	e : EdgeLand2		4
	S ; SideLand1		4
	s : SideLand2		4
	b : BorderDirt1		4
	B : BorderDirt2		4
	W : DeepWater2		4
	D : Dirt2			4
	d : DeepDirt2		4

	Mob :
	V : Vine			1
	N : Nennuphloat		1
	v : Station Vitale	1
	U : Bulb			6
	T : Thorn			1
	F : Fongus			3
	I : Ivy				3
	R : Bramble			1
	P : Bridge			1
	w : Wall			1
	O : Root			3
	*/

	for (size_t y = 0; y < map.size(); ++y)
	{
		for (size_t x = 0; x < map[y].size(); ++x) 
		{
			if (map[y][x] == 'X') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White, 4);
				block->GetAnimations()->LoadAnimationGrid("Land2");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'D') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White, 4);
				block->GetAnimations()->LoadAnimationGrid("Dirt3");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(false);
				block->GetHitbox()->hasHitbox = false; 
			}
			else if (map[y][x] == 'd') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White, 4);
				block->GetAnimations()->LoadAnimationGrid("DeepDirt2");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(false);
				block->GetHitbox()->hasHitbox = false;
			}
			else if (map[y][x] == 'L') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White, 4);
				block->GetAnimations()->LoadAnimationGrid("BorderLand1");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'l') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White, 4);
				block->GetAnimations()->LoadAnimationGrid("CornerLand5");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'C') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White, 4);
				block->GetAnimations()->LoadAnimationGrid("CornerLand3");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'c') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White, 4);
				block->GetAnimations()->LoadAnimationGrid("CornerLand4");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'E') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White, 4);
				block->GetAnimations()->LoadAnimationGrid("EdgeLand1");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'e') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White, 4);
				block->GetAnimations()->LoadAnimationGrid("EdgeLand2");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'S') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White, 4);
				block->GetAnimations()->LoadAnimationGrid("SideLand1");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
			}
			else if (map[y][x] == 's') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White, 4);
				block->GetAnimations()->LoadAnimationGrid("SideLand2");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'b') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White, 4);
				block->GetAnimations()->LoadAnimationGrid("BorderDirt1");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'B') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White, 4);
				block->GetAnimations()->LoadAnimationGrid("BorderDirt2");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'W') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White, 4);
				block->GetAnimations()->LoadAnimationGrid("DeepWater2");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(false);
				block->GetHitbox()->hasHitbox = false; 
			}




			else if (map[y][x] == 'V') {
				Vine* vine = CreateEntity<Vine>({ MOB_SIZE.x, MOB_SIZE.y }, sf::Color(172, 210, 128), 1);
				vine->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'N') {
				Nenuphloat* nenuphloat = CreateEntity<Nenuphloat>({ MOB_SIZE.x, MOB_SIZE.y }, sf::Color(65, 106, 36), 1);
				nenuphloat->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'v') {
				Station* station = CreateEntity<Station>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color(158, 144, 193), 1);
				station->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y - 50.f );
			}
			else if (map[y][x] == 'U') {
				Bulb* bulb = CreateEntity<Bulb>({ MOB_SIZE.x, MOB_SIZE.y }, sf::Color(213, 170, 63), 6);
				bulb->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'T') {
				Thorn* thorn = CreateEntity<Thorn>({ MOB_SIZE.x, MOB_SIZE.y }, sf::Color(133, 46, 46), 1);
				thorn->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'F') {
				Fongus* fongus = CreateEntity<Fongus>({ MOB_SIZE.x, MOB_SIZE.y }, sf::Color(0, 255, 0), 3);
				fongus->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'I') {
				Ivy* ivy = CreateEntity<Ivy>({ MOB_SIZE.x, MOB_SIZE.y }, sf::Color(254, 237, 92), 3);
				ivy->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'R') {
				Bramble* bramble = CreateEntity<Bramble>({ MOB_SIZE.x, MOB_SIZE.y }, sf::Color(66, 44, 40), 1);
				bramble->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'P') {
				Bridge* bridge = CreateEntity<Bridge>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color(122, 112, 112), 1);
				bridge->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'w') {
				Wall* wall = CreateEntity<Wall>({ MOB_SIZE.x, MOB_SIZE.y * 3 }, sf::Color(141, 49, 20), 1);
				wall->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y - BLOCK_SIZE.y);
			}
			else if (map[y][x] == 'O') {
				Root* root = CreateEntity<Root>({ BLOCK_SIZE.x * 5, MOB_SIZE.y}, sf::Color(120, 120, 10), 3);
				root->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y + BLOCK_SIZE.y / 2);
			}

			else if (map[y][x] == 'H') {
				End* end = CreateEntity<End>({ BLOCK_SIZE.x * 2, BLOCK_SIZE.y * 8}, sf::Color::White, 1);
				end->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y - 50.f * 3); 
			}
		}
	}

	assetManager->GetMusic("MainMusic")->play();
}

void TestScene::OnEvent(const sf::Event& event)
{
}

void TestScene::OnUpdate()
{
	float dt = GetDeltaTime();

	if (mCam.GetFocus() == true)
	{
		mCam.FollowPlayer();
	}

	UpdateCamera();

	SoundManager();
}

void TestScene::UpdateCamera()
{
	sf::Vector2f camSize = mCam.GetSize();
	sf::Vector2f pPos = GetPlayer()->GetPosition();
	sf::Vector2f posLimite = sf::Vector2f(100000, 875);

	float minX = 500 + camSize.x / 2;
	float maxX = posLimite.x - camSize.x / 2;
	float minY = camSize.y / 2;
	float maxY = posLimite.y - camSize.y / 2;

	float newCamX = std::clamp(pPos.x, minX, maxX);
	float newCamY = std::clamp(pPos.y, minY, maxY);

	if (mCam.GetFocus() == true)
	{
		mCam.SetPosition({ newCamX, newCamY });
	}
	
	GameManager::Get()->SetCamera(mCam);
}

bool TestScene::IsAllowedToCollide(int tag1, int tag2)
{
	return mInteractions[tag1][tag2];
}

void TestScene::InitSounds()
{
	assetManager->LoadMusic("MainMusic", "../../../res/Assets/music/mainmusic.wav")->setLoop(true);
	assetManager->GetMusic("MainMusic")->setVolume(100 * mVolume);
	assetManager->LoadSound("Waterdrop", "../../../res/Assets/sfx/waterdrop.wav")->setVolume(100 * mVolume);
	assetManager->LoadSound("WeedKiller", "../../../res/Assets/sfx/weedkiller.wav")->setVolume(75 * mVolume);
	assetManager->GetSound("WeedKiller")->setLoop(true);
	assetManager->LoadSound("Checkpoint", "../../../res/Assets/sfx/checkpoint.wav")->setVolume(50 * mVolume);
	assetManager->LoadSound("ReloadWater", "../../../res/Assets/sfx/reloadwater.wav")->setVolume(30 * mVolume);
	assetManager->LoadSound("PlayerJump", "../../../res/Assets/sfx/jump.wav")->setVolume(50 * mVolume);
	assetManager->LoadSound("PlayerShooting", "../../../res/Assets/sfx/shooting.wav")->setVolume(100 * mVolume);
	assetManager->LoadSound("PlayerDash", "../../../res/Assets/sfx/dash.wav")->setVolume(50 * mVolume);
	assetManager->LoadSound("Landing", "../../../res/Assets/sfx/landing.wav")->setVolume(25 * mVolume);
	assetManager->LoadSound("Bonk", "../../../res/Assets/sfx/bonk.wav")->setVolume(25 * mVolume);
	assetManager->LoadSound("Falling", "../../../res/Assets/sfx/falling.wav")->setVolume(50 * mVolume);
	assetManager->LoadSound("Hurt", "../../../res/Assets/sfx/hurt.wav")->setVolume(75 * mVolume);
	assetManager->LoadSound("Dead", "../../../res/Assets/sfx/dead.wav")->setVolume(25 * mVolume);
	assetManager->LoadSound("Button", "../../../res/Assets/sfx/button.wav")->setVolume(30 * mVolume);
	assetManager->LoadSound("DeadMonster", "../../../res/Assets/sfx/deadmonster.wav")->setVolume(75 * mVolume);
	assetManager->LoadSound("Revelation", "../../../res/Assets/sfx/revelation.wav")->setVolume(25 * mVolume);
	assetManager->LoadSound("Transition", "../../../res/Assets/sfx/transition.wav")->setVolume(25 * mVolume);
	assetManager->LoadSound("Suspense", "../../../res/Assets/sfx/suspense.wav")->setVolume(100 * mVolume);
}

void TestScene::SoundManager()
{
	if (mProgressToChangeVolume > mDelayToChangeVolume)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			AddRemoveVolume(-0.1f);

			UpdateVolume();

			mProgressToChangeVolume = 0.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			AddRemoveVolume(0.1f);

			UpdateVolume();


			mProgressToChangeVolume = 0.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			if (isStopSound == false)
			{
				isStopSound = true; 
				StopSound(); 
			}
			else
			{
				isStopSound = false; 
				UpdateVolume(); 
			}

			mProgressToChangeVolume = 0.f;
		}
	}
	else
	{
		mProgressToChangeVolume += GetDeltaTime();
	}
}

void TestScene::UpdateVolume() 
{
	if (isStopSound)
		return;

	assetManager->GetMusic("MainMusic")->setVolume(100 * mVolume);
	assetManager->GetSound("Waterdrop")->setVolume(100 * mVolume);
	assetManager->GetSound("WeedKiller")->setVolume(75 * mVolume);
	assetManager->GetSound("WeedKiller")->setLoop(true);
	assetManager->GetSound("Checkpoint")->setVolume(50 * mVolume);
	assetManager->GetSound("ReloadWater")->setVolume(30 * mVolume);
	assetManager->GetSound("PlayerJump")->setVolume(75 * mVolume);
	assetManager->GetSound("PlayerShooting")->setVolume(100 * mVolume);
	assetManager->GetSound("PlayerDash")->setVolume(50 * mVolume);
	assetManager->GetSound("Landing")->setVolume(25 * mVolume);
	assetManager->GetSound("Bonk")->setVolume(25 * mVolume);
	assetManager->GetSound("Falling")->setVolume(50 * mVolume);
	assetManager->GetSound("Hurt")->setVolume(75 * mVolume);
	assetManager->GetSound("Dead")->setVolume(25 * mVolume);
	assetManager->GetSound("Button")->setVolume(30 * mVolume);
	assetManager->GetSound("DeadMonster")->setVolume(75 * mVolume);
	assetManager->GetSound("Revelation")->setVolume(25 * mVolume);
	assetManager->GetSound("Transition")->setVolume(25 * mVolume);
	assetManager->GetSound("Suspense")->setVolume(100 * mVolume);
}

void TestScene::StopSound()
{
	assetManager->GetMusic("MainMusic")->setVolume(0);
	assetManager->GetSound("Waterdrop")->setVolume(0);
	assetManager->GetSound("WeedKiller")->setVolume(0);
	assetManager->GetSound("WeedKiller")->setLoop(true);
	assetManager->GetSound("Checkpoint")->setVolume(0);
	assetManager->GetSound("ReloadWater")->setVolume(0);
	assetManager->GetSound("PlayerJump")->setVolume(0);
	assetManager->GetSound("PlayerShooting")->setVolume(0);
	assetManager->GetSound("PlayerDash")->setVolume(0);
	assetManager->GetSound("Landing")->setVolume(0);
	assetManager->GetSound("Bonk")->setVolume(0);
	assetManager->GetSound("Falling")->setVolume(0);
	assetManager->GetSound("Hurt")->setVolume(0);
	assetManager->GetSound("Dead")->setVolume(0);
	assetManager->GetSound("Button")->setVolume(0);
	assetManager->GetSound("DeadMonster")->setVolume(0);
	assetManager->GetSound("Revelation")->setVolume(0);
	assetManager->GetSound("Transition")->setVolume(0);
	assetManager->GetSound("Suspense")->setVolume(0);
}

void TestScene::InitTextures()
{
	assetManager->LoadTexture("Terrain", "../../../res/Assets/Textures/SpriteSheet_Terrain.png");
	assetManager->LoadTexture("Hydro", "../../../res/Assets/Textures/SpriteSheet_Hydro.png");
	assetManager->LoadTexture("Nenuphloat", "../../../res/Assets/Textures/SpriteSheet_Nenuphloat.png");
	assetManager->LoadTexture("Vine", "../../../res/Assets/Textures/SpriteSheet_Liane.png");
	assetManager->LoadTexture("Station", "../../../res/Assets/Textures/SpriteSheet_Station.png");
	assetManager->LoadTexture("Bulb", "../../../res/Assets/Textures/SpriteSheet_BulbeLumina.png");
	assetManager->LoadTexture("Bramble", "../../../res/Assets/Textures/SpriteSheet_Bramble.png");
	assetManager->LoadTexture("Ivy", "../../../res/Assets/Textures/SpriteSheet_Ivy.png");
	assetManager->LoadTexture("Thorn", "../../../res/Assets/Textures/SpriteSheet_Thorn.png");
	assetManager->LoadTexture("Fongus", "../../../res/Assets/Textures/SpriteSheet_Fongus.png");
	assetManager->LoadTexture("FongusCloud", "../../../res/Assets/Textures/SpriteSheet_FongusCloud.png");
	assetManager->LoadTexture("BrambleExplosion", "../../../res/Assets/Textures/SpriteSheet_BrambleExplosion.png");
	assetManager->LoadTexture("Mist", "../../../res/Assets/Textures/SpriteSheet_Mist.png");
	assetManager->LoadTexture("Logo", "../../../res/Assets/Textures/Logo.png");  
	assetManager->LoadTexture("BG", "../../../res/Assets/Textures/bg.png");
	assetManager->LoadTexture("Water", "../../../res/Assets/Textures/SpriteSheet_Water.png");
	assetManager->LoadTexture("ThornWall", "../../../res/Assets/Textures/SpriteSheet_ThornWall.png");
	assetManager->LoadTexture("Bridge", "../../../res/Assets/Textures/SpriteSheet_Bridge.png");
	assetManager->LoadTexture("Root", "../../../res/Assets/Textures/SpriteSheet_Root.png");
	assetManager->LoadTexture("Dash", "../../../res/Assets/Textures/SpriteSheet_Dash.png");
}

void TestScene::InitAssets()
{
	InitSounds();
	InitTextures();
}

void TestScene::InitTransitions()
{
	for (int i = 0; i < TAG_COUNT; i++)
	{
		for (int j = 0; j < TAG_COUNT; j++)
		{
			mInteractions[i][j] = false;
		}
	}

	SetInteractionWith(TPlayer, TPlatform, true);
	SetInteractionWith(TWater, TPlatform, true); 

	SetInteractionWith(TPlayer, TAlly, true);
	SetInteractionWith(TPlayer, TEnemy, true);

	SetInteractionWith(TWater, TAlly, true);
	SetInteractionWith(TAcid, TEnemy, true);

	SetInteractionWith(TPlayer, TObstacle, true);
	SetInteractionWith(TWater, TObstacle, true);
	SetInteractionWith(TPlatform, TObstacle, true);
	SetInteractionWith(TAcid, TObstacle, true);

	SetInteractionWith(TPlayer, TEnd, true);
}

void TestScene::AddRemoveVolume(float value)
{
	if (mProgressToChangeVolume <= mDelayToChangeVolume || isStopSound)
		return;

	mVolume += value;

	if (mVolume > 1)
	{
		mVolume = 1;
		return;
	}

	if (mVolume <= 0)
	{
		mVolume = 0;
		return;
	}

	assetManager->GetSound("Button")->play();
}
