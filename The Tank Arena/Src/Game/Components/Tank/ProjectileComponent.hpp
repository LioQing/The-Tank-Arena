#pragma once

#include <LioGraphics.hpp>
#include <lic.hpp>

struct ProjectileComponent : lic::Component
{
	uint32_t bounce_counter = 0u;
	uint32_t bounce_count;

	lio::Vec2f start_pt = lio::Vec2f::Zero();

	ProjectileComponent(uint32_t bounce_count, const lio::Vec2f& start_pt);
};