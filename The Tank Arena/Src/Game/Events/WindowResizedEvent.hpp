#pragma once

#include <lev.hpp>

#include "../../ProgramUtils.hpp"

struct WindowResizedEvent : lev::Event
{
	const Scale& previous_scale;
	const Scale& current_scale;

	WindowResizedEvent(const Scale& previous_scale, const Scale& current_scale);
};