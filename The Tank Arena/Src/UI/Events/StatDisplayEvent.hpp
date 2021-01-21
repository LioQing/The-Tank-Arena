#pragma once

#include <lev.hpp>

struct StatDisplayEvent : lev::Event
{
	uint32_t tank_destroyed;
	uint32_t bullet_fired;

	StatDisplayEvent(uint32_t tank_destroyed, uint32_t bullet_fired);
};