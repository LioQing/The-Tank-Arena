#pragma once

#include <lev.hpp>

#include "../Program.hpp"

struct StateChangeEvent : public lev::Event
{
	Program::State state;

	StateChangeEvent(Program::State state);
};