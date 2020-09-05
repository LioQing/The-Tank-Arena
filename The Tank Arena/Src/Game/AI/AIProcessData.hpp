#pragma once

#include <Matrix.hpp>
#include <LioGraphics.hpp>
#include <map>

#include "../Components.hpp"
#include "../../ProgramUtils.hpp"

struct AIProcessData
{
	lio::Vec2f player_pos;
	std::map<lic::EntityID, lio::Vec2f> ai_pos;

	LevelComponent level;
	Scale scale;
};