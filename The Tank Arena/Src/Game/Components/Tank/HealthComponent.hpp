#pragma once

#include <lic.hpp>

struct HealthComponent : lic::Component
{
	bool is_dead = false;
};