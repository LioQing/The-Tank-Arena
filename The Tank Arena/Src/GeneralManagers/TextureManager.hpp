#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <tuple>

class TextureManager
{
private:

	struct TextureInfo
	{
		sf::Texture texture;
		std::string path;

		TextureInfo() = default;
		TextureInfo(sf::Texture& texture, const std::string& path);
	};

	std::map<std::string, TextureInfo> m_textures;

public:

	sf::Texture* LoadTexture(const std::string& id, const std::string& path);
	void UnloadTexture(const std::string& id);

	std::pair<sf::Texture*, sf::Texture*> LoadTankTexture(const std::string& id, const std::string& path);
	void UnloadTankTexture(const std::string& id);

	std::tuple<sf::Texture*, sf::Texture*, sf::Texture*> LoadButtonTexture(const std::string& id, const std::string& path);
	void UnloadButtonTexture(const std::string& id);

	sf::Texture* GetTexture(const std::string& id);
	const std::string& GetTexturePath(const std::string& id) const;
};