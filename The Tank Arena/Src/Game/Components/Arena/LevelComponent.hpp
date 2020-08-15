#pragma once

#include <vector>
#include <lic.hpp>
#include <Matrix.hpp>
#include <LioGraphics.hpp>

struct LevelComponent : lic::Component
{
	std::vector<lio::Vec2i> walls;
	lio::Matrixi level;
	lio::Vec2i size;
	int tile_size;

	LevelComponent(int width, int height, int tile_size);
};