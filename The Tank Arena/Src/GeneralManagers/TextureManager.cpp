#include "TextureManager.hpp"

#include <iostream>

TextureManager::TextureInfo::TextureInfo(sf::Texture& texture, const std::string& path)
	: texture(texture), path(path)
{
}

sf::Texture* TextureManager::LoadTexture(const std::string& id, const std::string& path)
{
	sf::Texture texture;

	if (!texture.loadFromFile(path))
	{
		std::cerr << "Error: could not load texture - id: " << id << ", path: " << path << std::endl;
		return nullptr;
	}

	m_textures[id] = TextureInfo(texture, path);
	return &m_textures[id].texture;
}

std::pair<sf::Texture*, sf::Texture*> TextureManager::LoadTankTexture(const std::string& id, const std::string& path)
{
	auto hull = LoadTexture(id + "_hull", path + "\\" + id + "\\hull.png");
	auto turret = LoadTexture(id + "_turret", path + "\\" + id + "\\turret.png");
	return { hull, turret };
}

sf::Texture* TextureManager::GetTexture(const std::string& id)
{
	if (m_textures.find(id) == m_textures.end())
	{
		std::cerr << "Error: could not get texture - id: " << id << std::endl;
		return nullptr;
	}
	return &m_textures.at(id).texture;
}

const std::string& TextureManager::GetTexturePath(const std::string& id) const
{
	if (m_textures.find(id) == m_textures.end())
	{
		std::cerr << "Error: could not get texture - id: " << id << std::endl;
		return nullptr;
	}
	return m_textures.at(id).path;
}
