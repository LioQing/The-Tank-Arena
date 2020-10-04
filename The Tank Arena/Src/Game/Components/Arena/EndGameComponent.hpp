#pragma once

#include <lic.hpp>

struct EndGameComponent : lic::Component
{
	bool is_ended = false;

	float timer = 0.f;
	const float countdown;

	EndGameComponent(float countdown);
};