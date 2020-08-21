#pragma once

#include <lic.hpp>

struct ProjectileComponent : lic::Component
{
	const float decay;
	float decay_timer = 0.f;

	ProjectileComponent(float decay);
};