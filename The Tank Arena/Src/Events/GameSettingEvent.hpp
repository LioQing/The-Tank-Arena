#pragma once

#include <SFML/Graphics.hpp>
#include <lev.hpp>

struct GameSettingEvent : lev::Event
{
	const sf::Color& crosshair_line_col;
	const sf::Color& crosshair_col;
	float crosshair_line_thickness;

	GameSettingEvent(
		const sf::Color& crosshair_col,
		const sf::Color& crosshair_line_col,
		float crosshair_line_thickness);
};