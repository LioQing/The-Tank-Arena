#include "PlayerControlComponent.hpp"

PlayerControlComponent::PlayerControlComponent()
	: movement(0.f, 0.f), turret_dir(0.f, 0.f), fire(false)
{
}

const lio::Vec2f& PlayerControlComponent::GetMovement() const
{
	return movement;
}
