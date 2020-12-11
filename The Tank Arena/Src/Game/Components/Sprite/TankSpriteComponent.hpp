#pragma once

#include <SFML/Graphics.hpp>
#include <lic.hpp>

#include "../../../ProgramUtils.hpp"

struct TankSpriteComponent : lic::Component
{
	static const uint32_t tex_rect_size = 32;

	sf::Sprite hull_sprite, turret_sprite;

	TankSpriteComponent(ProgramInfo& program_info, const std::string& hull_id, const std::string& turret_id);
};