#include "TankTransformComponent.hpp"

TankTransformComponent::TankTransformComponent(lio::Vec2i size, float speed, float turret_a_speed)
	: speed(speed), turret_a_speed(turret_a_speed), size(size)
{
}