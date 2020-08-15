#pragma once

#include <array>
#include <lic.hpp>
#include <LioGraphics.hpp>

struct TankColliderComponent : lic::Component
{
	std::array<lio::Vec2f, 2> pts;
};