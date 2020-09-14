#pragma once

#include <array>
#include <lic.hpp>
#include <LioGraphics.hpp>

struct TankColliderComponent : lic::Component
{
	std::array<lio::Vec2f, 2> pts;

	float tank_collide_radius;
	float tank_repulsion;

	TankColliderComponent(float tank_collide_radius, float tank_repulsion);
};