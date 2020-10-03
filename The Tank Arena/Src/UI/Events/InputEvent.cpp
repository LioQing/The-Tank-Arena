#include "InputEvent.hpp"

InputEvent::InputEvent(const lio::Vec2f& mouse_pos, sf::Mouse::Button button)
	: mouse_pos(mouse_pos), button(button)
{
}

InputEvent::InputEvent(bool is_mouse_down)
	: is_mouse_down(is_mouse_down)
{
}
