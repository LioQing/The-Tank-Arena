#pragma once

#include <lev.hpp>

struct TimerEvent : public lev::Event
{
	float dt;

	TimerEvent(float dt);
};