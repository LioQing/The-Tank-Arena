#pragma once

#include <lev.hpp>

#include "../Program.hpp"

struct LevelChangeEvent : public lev::Event
{
	uint32_t level;

	LevelChangeEvent(uint32_t level);
};