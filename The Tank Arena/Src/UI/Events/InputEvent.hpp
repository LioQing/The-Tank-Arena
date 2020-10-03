#pragma once

#include <SFML/Graphics.hpp>
#include <LioGraphics.hpp>
#include <lev.hpp>

struct InputEvent : lev::Event
{
	sf::Mouse::Button button;
	lio::Vec2f mouse_pos;
	bool is_mouse_down = true;

	InputEvent(const lio::Vec2f& mouse_pos, sf::Mouse::Button button);
	InputEvent(bool is_mouse_down);
};