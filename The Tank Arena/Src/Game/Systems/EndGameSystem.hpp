#pragma once

#include "System.hpp"

struct EndGameSystem : System
{
	EndGameSystem(uint32_t* program_state);

	void Update() override;

private:

	uint32_t* program_state = nullptr;
};