#pragma once

#include <SFML/Graphics.hpp>
#include <LioGraphics.hpp>
#include <lev.hpp>

struct InputEvent : lev::Event
{
	sf::Mouse::Button button;
	lio::Vec2f mouse_pos;
	bool is_mouse_down = true;
	bool is_hover = false;

	InputEvent(const lio::Vec2f& mouse_pos, sf::Mouse::Button button);
	InputEvent(bool is_mouse_down, const lio::Vec2f& mouse_pos);
	InputEvent(const lio::Vec2f& mouse_pos, bool is_hover, bool is_mouse_down);
};