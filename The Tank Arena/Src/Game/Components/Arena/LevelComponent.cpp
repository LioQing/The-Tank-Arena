#include "LevelComponent.hpp"

LevelComponent::LevelComponent(int width, int height, int tile_size)
	: size(width, height), level(width, height, Cell()), tile_size(tile_size)
{
}

lio::Vec2i Cell::DirToVec(Dir dir)
{
	switch (dir)
	{
		case UP:
			return lio::Vec2i::Up();
		
		case DOWN:
			return lio::Vec2i::Down();

		case LEFT:
			return lio::Vec2i::Left();

		case RIGHT:
			return lio::Vec2i::Right();

		default:
			return lio::Vec2i::Zero();
	}
}

Cell::Dir Cell::VecToDir(const lio::Vec2i& dir)
{
	if (dir == lio::Vec2i::Up())
		return UP;
	else if (dir == lio::Vec2i::Down())
		return DOWN;
	else if (dir == lio::Vec2i::Left())
		return LEFT;
	else
		return RIGHT;
}

Cell::operator int() const
{
	return id;
}
