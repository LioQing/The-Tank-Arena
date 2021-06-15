#pragma once

#include <lic.hpp>

struct TurretComponent : lic::Component
{
	float radius;

	float interval;
	float interval_timer = 0.f;

	uint32_t bullet_count;
	uint32_t bullet_counter = 0;

	uint32_t bounce_count;
	float speed;

	TurretComponent(float speed, float interval, uint32_t bounce_count, uint32_t bullet_count, float turret_radius);
};