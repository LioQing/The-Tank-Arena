#pragma once

#include <SFML/Graphics.hpp>
#include <lev.hpp>

struct UIRescaleEvent : lev::Event
{
	const sf::View& view;
	float scale;

	UIRescaleEvent(float scale, const sf::View& view);
};