#pragma once

#include <lic.hpp>

struct TurretComponent : lic::Component
{
	float interval;
	float interval_timer = 0.f;

	uint32_t bounce_count;
	float speed;

	TurretComponent(float speed, float interval, uint32_t bounce_count);
};