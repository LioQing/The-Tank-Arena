#include "AIControlComponent.hpp"

AIControlComponent::AIControlComponent(float turret_speed)
	: turret_speed(turret_speed)
{
	turret_dir.store(std::make_shared<lio::Vec2f>(0.f, 0.f));
}
