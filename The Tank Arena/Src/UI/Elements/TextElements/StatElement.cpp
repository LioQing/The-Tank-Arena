#include "StatElement.hpp"

#include "../../Events.hpp"

StatElement::StatElement(Type type)
	: type(type)
{
	Listen<StatDisplayEvent>();
}

void StatElement::On(const lev::Event& event)
{
	if (event.Is<StatDisplayEvent>())
	{
		const auto& stat_display = static_cast<const StatDisplayEvent&>(event);

		if (type == Type::BULLET_SHOT)
			SetText("Bullet Shot: " + std::to_string(stat_display.bullet_fired));
		else if (type == Type::TANK_DESTROYED)
			SetText("Tank Destroyed: " + std::to_string(stat_display.tank_destroyed));
	}
}
