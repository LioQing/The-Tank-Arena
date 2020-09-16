#pragma once

#include <Matrix.hpp>
#include <LioGraphics.hpp>
#include <map>

#include "../Components.hpp"
#include "../../ProgramUtils.hpp"

struct AIProcessData
{
	struct AISpecificData
	{
		lio::Vec2f position;
		bool is_dead;
	};

	lio::Vec2f player_pos;
	std::map<lic::EntityID, AISpecificData> ai_data;

	LevelComponent level;
	Scale scale;
	float dt;
};