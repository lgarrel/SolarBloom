#pragma once
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>

class AssetManager
{
	static AssetManager* instance;

	//Stock avec les noms
	std::map<const char*, sf::Texture*> mTextures;
	std::map<const char*, sf::Sound*> mSounds;
	std::map<const char*, sf::Music*> mMusics;

	//Nom puis le Path
	std::map<const char*, const char*> mTexturesPaths;
	std::map<const char*, const char*> mSoundsPaths;
	std::map<const char*, const char*> mMusicPaths;

public:
	static AssetManager* Get();

	//Il faut Load la texture avant de pouvoir la Get correctement
	sf::Texture* LoadTexture(const char* alias, const char* path);
	sf::Sound* LoadSound(const char* alias, const char* path);
	sf::Music* LoadMusic(const char* alias, const char* path);

	sf::Texture* GetTexture(const char* alias);
	sf::Sound* GetSound(const char* alias);
	sf::Music* GetMusic(const char* alias);
};

