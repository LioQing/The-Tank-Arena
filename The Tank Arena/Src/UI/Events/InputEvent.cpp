#include "InputEvent.hpp"

InputEvent::InputEvent(const lio::Vec2f& mouse_pos, sf::Mouse::Button button)
	: mouse_pos(mouse_pos), button(button), is_click(true)
{
}

InputEvent::InputEvent(const lio::Vec2f& mouse_pos, bool is_hover, bool is_release)
	: mouse_pos(mouse_pos), is_hover(is_hover), is_release(is_release)
{
}
