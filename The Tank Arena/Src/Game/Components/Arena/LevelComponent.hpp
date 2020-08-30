#pragma once

#include <array>
#include <vector>
#include <lic.hpp>
#include <Matrix.hpp>
#include <LioGraphics.hpp>

#include "../../../ProgramUtils.hpp"

struct Cell
{
	int32_t id;
	std::array<bool, 4> edge_exist;
	std::array<size_t, 4> edge_id;

	operator int32_t() const;
};

struct Edge
{
	lio::LineSegi edge;
	Dir::Dir dir;

	operator lio::LineSegi() const;
};

struct LevelComponent : lic::Component
{
	lio::Matrix<Cell> level;
	std::vector<Edge> edge_pool;

	lio::Vec2i size;
	size_t tile_size;

	LevelComponent(size_t width, size_t height, size_t tile_size);
};