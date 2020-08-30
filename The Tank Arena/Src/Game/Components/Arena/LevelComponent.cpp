#include "LevelComponent.hpp"

LevelComponent::LevelComponent(size_t width, size_t height, size_t tile_size)
	: size(width, height), level(width, height, Cell()), tile_size(tile_size)
{
}

Cell::operator int32_t() const
{
	return id;
}

Edge::operator lio::LineSegi() const
{
	return edge;
}
