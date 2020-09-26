#pragma once

#include <SFML/Graphics.hpp>
#include <lev.hpp>

struct InGameCursorEvent : lev::Event
{
	sf::Vector2f pos;

	InGameCursorEvent(const sf::Vector2f& pos);
};