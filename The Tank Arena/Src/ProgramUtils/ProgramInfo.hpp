#pragma once

#include <SFML/Graphics.hpp>

#include "../GeneralManagers/TextureManager.hpp"
#include "Scale.hpp"

struct ProgramInfo
{
	Scale* scale;
	sf::RenderWindow* window;
	TextureManager* texture_manager;

	ProgramInfo() = default;
	ProgramInfo(Scale& scale, sf::RenderWindow& window, TextureManager& tex_man);
};