#ifndef ASSET_MANAGER_H_INCLUDED
#define ASSET_MANAGER_H_INCLUDED

#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<assert.h>
#include<unordered_map>
#include<memory>

class AssetManager
{
public:
	AssetManager();

	static sf::Texture& GetTexture(const std::string& filename);
	static sf::SoundBuffer& GetSoundBuffer(const std::string& filename);
	static sf::Font& GetFont(const std::string & filename);
	static sf::Shader* GetShader(const std::string& vsFile,const std::string& fsFile);

private:
	std::unordered_map<std::string, sf::Texture>                  m_Textures;
	std::unordered_map<std::string, sf::SoundBuffer>              m_SoundBuffer;
	std::unordered_map<std::string, sf::Font>                     m_Fonts;
	std::unordered_map<std::string, std::unique_ptr<sf::Shader>>  m_Shaders;

	static AssetManager* sInstance;
};

#endif // ASSET_MANAGER_H_INCLUDED
