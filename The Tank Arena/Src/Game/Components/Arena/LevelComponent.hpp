#pragma once

#include <array>
#include <vector>
#include <lic.hpp>
#include <Matrix.hpp>
#include <LioGraphics.hpp>

struct Cell
{
	enum Dir : int8_t
	{
		UP, DOWN, LEFT, RIGHT
	};

	static lio::Vec2i DirToVec(Dir dir);
	static Dir VecToDir(const lio::Vec2i& dir);

	int id;
	std::array<bool, 4> edge_exist;
	std::array<int, 4> edge_id;

	operator int() const;
};

struct LevelComponent : lic::Component
{
	std::vector<lio::Vec2i> walls;
	lio::Matrix<Cell> level;
	std::vector<lio::LineSegi> edge_pool;

	lio::Vec2i size;
	int tile_size;

	LevelComponent(int width, int height, int tile_size);
};