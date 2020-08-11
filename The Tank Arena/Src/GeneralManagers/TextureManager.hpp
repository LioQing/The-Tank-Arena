#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class TextureManager
{
private:

	std::map<std::string, sf::Texture> m_textures;

public:

	sf::Texture* LoadTexture(const std::string& id, const std::string& path);
	sf::Texture* GetTexture(const std::string& id);
};