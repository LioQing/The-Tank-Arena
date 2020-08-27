#pragma once

#include <SFML/Graphics.hpp>
#include <LioGraphics.hpp>
#include <lic.hpp>

struct HUDComponent : lic::Component
{
	lio::Vec2f crosshair_pos;
	sf::RectangleShape crosshair_line;

	HUDComponent();
};