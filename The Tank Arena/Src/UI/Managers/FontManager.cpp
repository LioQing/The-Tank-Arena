#include "FontManager.hpp"

#include <iostream>

sf::Font* FontManager::LoadFont(const std::string& id, const std::string& path)
{
    sf::Font font;

    if (!font.loadFromFile(path))
    {
        std::cerr << "Error: could not load font - id: " << id << ", path: " << path << std::endl;
        return nullptr;
    }
    
    fonts.insert({ id, font });
    return &fonts[id];
}

const sf::Font* FontManager::GetFont(const std::string& id) const
{
    if (fonts.find(id) == fonts.end())
    {
        std::cerr << "Error: could not get font - id: " << id << std::endl;
        return nullptr;
    }
    return &fonts.at(id);
}
