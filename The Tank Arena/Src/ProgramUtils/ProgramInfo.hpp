#pragma once

#include <SFML/Graphics.hpp>

#include "../GeneralManagers/TextureManager.hpp"
#include "Scale.hpp"

struct ProgramInfo
{
	const uint32_t* current_level;
	Scale* scale;
	sf::RenderWindow* window;
	TextureManager* texture_manager;

	ProgramInfo() = default;
	ProgramInfo(sf::RenderWindow& window, TextureManager& tex_man, const uint32_t& level);
};