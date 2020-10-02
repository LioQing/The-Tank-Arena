#include "ButtonElement.hpp"

void ButtonElement::SetTrigger(const lio::Rect<float>& rect)
{
	trigger_rect = rect;
}

const lio::Rect<float>& ButtonElement::GetTrigger() const
{
	return trigger_rect;
}
