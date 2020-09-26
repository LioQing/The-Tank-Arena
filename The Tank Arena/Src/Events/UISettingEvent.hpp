#pragma once

#include <SFML/Graphics.hpp>
#include <lev.hpp>

struct UISettingEvent : lev::Event
{
	sf::Color crosshair_col;

	UISettingEvent(const sf::Color& crosshair_col);
};