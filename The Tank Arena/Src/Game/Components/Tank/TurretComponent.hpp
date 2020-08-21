#pragma once

#include <lic.hpp>

struct TurretComponent : lic::Component
{
	float interval;
	float interval_timer = 0.f;

	float decay;
	float speed;

	TurretComponent(float speed, float interval, float decay);
};