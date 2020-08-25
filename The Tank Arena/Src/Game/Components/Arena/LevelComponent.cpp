#include "LevelComponent.hpp"

LevelComponent::LevelComponent(int width, int height, int tile_size)
	: size(width, height), level(width, height, Cell()), tile_size(tile_size)
{
}

lio::Vec2i Cell::DirToVec(Dir dir)
{
	switch (dir)
	{
		case Dir::DOWN:
			return lio::Vec2i::Up();
		
		case Dir::UP:
			return lio::Vec2i::Down();

		case Dir::LEFT:
			return lio::Vec2i::Left();

		case Dir::RIGHT:
			return lio::Vec2i::Right();

		default:
			return lio::Vec2i::Zero();
	}
}

Cell::Dir Cell::VecToDir(const lio::Vec2i& dir)
{
	if (dir == lio::Vec2i::Up())
		return Dir::DOWN;
	else if (dir == lio::Vec2i::Down())
		return Dir::UP;
	else if (dir == lio::Vec2i::Left())
		return Dir::LEFT;
	else
		return Dir::RIGHT;
}

Cell::operator int() const
{
	return id;
}

Edge::operator lio::LineSegi() const
{
	return edge;
}
