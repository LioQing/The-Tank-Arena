#pragma once

#include <LioGraphics.hpp>
#include <lic.hpp>

struct ProjectileComponent : lic::Component
{
	const float decay;
	float decay_timer = 0.f;

	lio::Vec2f start_pt = lio::Vec2f::Zero();

	ProjectileComponent(float decay, const lio::Vec2f& start_pt);
};