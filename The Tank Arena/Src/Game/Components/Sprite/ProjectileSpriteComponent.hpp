#pragma once

#include <SFML/Graphics.hpp>
#include <lic.hpp>

#include "../../../ProgramUtils.hpp"

struct ProjectileSpriteComponent : lic::Component
{
	sf::Sprite sprite;

	ProjectileSpriteComponent(ProgramInfo& program_info, const std::string& id);
};