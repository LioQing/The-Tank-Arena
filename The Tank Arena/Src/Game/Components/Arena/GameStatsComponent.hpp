#pragma once

#include <lic.hpp>

struct GameStatsComponent : lic::Component
{
	uint32_t tank_destroyed = 0;
	uint32_t bullet_fired = 0;
};