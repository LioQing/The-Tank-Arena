#pragma once

#include <Matrix.hpp>
#include <LioGraphics.hpp>
#include <unordered_map>
#include <memory>
#include <atomic>

#include "../Components.hpp"

struct AIProcessData
{
	std::atomic<lio::Vec2f*> player_pos;
	std::map<lic::EntityID, std::atomic<lio::Vec2f*>> ai_pos;

	lio::Matrix<int8_t> map;
};