#pragma once

#include <SFML/Graphics.hpp>
#include <lic.hpp>
#include <LioGraphics.hpp>

#include "../../../ProgramUtils.hpp"

struct GunfireSpriteComponent : lic::Component
{
	sf::Sprite sprite;
	float timer = 500.f;

	GunfireSpriteComponent(ProgramInfo& program_info, const lio::Vec2f& pos, float rot);
};