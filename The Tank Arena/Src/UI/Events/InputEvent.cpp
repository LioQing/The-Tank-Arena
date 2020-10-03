#include "InputEvent.hpp"

InputEvent::InputEvent(const lio::Vec2f& mouse_pos, sf::Mouse::Button button)
	: mouse_pos(mouse_pos), button(button)
{
}

InputEvent::InputEvent(bool is_mouse_down, const lio::Vec2f& mouse_pos)
	: is_mouse_down(is_mouse_down), mouse_pos(mouse_pos)
{
}

InputEvent::InputEvent(const lio::Vec2f& mouse_pos, bool is_hover, bool is_mouse_down)
	: mouse_pos(mouse_pos), is_hover(is_hover), is_mouse_down(is_mouse_down)
{
}
