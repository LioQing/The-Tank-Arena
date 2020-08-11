#include "TextureManager.hpp"

#include <iostream>

sf::Texture* TextureManager::LoadTexture(std::string id, const std::string& path)
{
	sf::Texture* texture = new sf::Texture();

	if (!texture->loadFromFile(path))
	{
		std::cerr << "Error: could not load texture - id: " << id << ", path: " << path << std::endl;
		return nullptr;
	}

	m_textures[id] = texture;
	return m_textures[id];
}

sf::Texture* TextureManager::GetTexture(const std::string& id)
{
	if (m_textures.find(id) == m_textures.end())
	{
		std::cerr << "Error: could not get texture - id: " << id << std::endl;
		return nullptr;
	}
	return m_textures.at(id);
}
