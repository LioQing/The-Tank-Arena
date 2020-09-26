#pragma once

#include <SFML/Graphics.hpp>
#include <lev.hpp>

struct GameSettingEvent : lev::Event
{
	sf::Color crosshair_line_col;
	float crosshair_line_thickness;

	sf::Color tank_col;

	GameSettingEvent(
		const sf::Color& tank_col,
		const sf::Color& crosshair_line_col,
		float crosshair_line_thickness);
};