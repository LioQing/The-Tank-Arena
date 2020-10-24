#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class FontManager
{
private:

	std::map<std::string, sf::Font> fonts;

public:

	sf::Font* LoadFont(const std::string& id, const std::string& path);
	const sf::Font* GetFont(const std::string& id) const;
};