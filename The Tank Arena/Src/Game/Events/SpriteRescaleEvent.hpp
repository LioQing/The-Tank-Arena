#pragma once

#include <lev.hpp>

#include "../../ProgramUtils.hpp"

struct SpriteRescaleEvent : lev::Event
{
	const Scale& previous_scale;
	const Scale& current_scale;

	SpriteRescaleEvent(const Scale& previous_scale, const Scale& current_scale);
};