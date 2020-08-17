#pragma once

#include <lic.hpp>
#include <LioGraphics.hpp>

struct PlayerControlComponent : lic::Component
{
	lio::Vec2f movement;
	lio::Vec2f turret_dir;

	PlayerControlComponent();
};