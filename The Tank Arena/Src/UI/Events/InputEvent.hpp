#pragma once

#include <SFML/Graphics.hpp>
#include <LioGraphics.hpp>
#include <lev.hpp>

struct InputEvent : lev::Event
{
	sf::Mouse::Button button;
	lio::Vec2f mouse_pos;
	bool is_click = false;
	bool is_hover = false;
	bool is_release = false;

	InputEvent(const lio::Vec2f& mouse_pos, sf::Mouse::Button button);
	InputEvent(const lio::Vec2f& mouse_pos, bool is_hover, bool is_release);
};