#include "SpriteRescaleEvent.hpp"

SpriteRescaleEvent::SpriteRescaleEvent(const Scale& previous_scale, const Scale& current_scale)
	: previous_scale(previous_scale), current_scale(current_scale)
{
}
