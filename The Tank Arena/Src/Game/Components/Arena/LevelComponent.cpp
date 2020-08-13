#include "LevelComponent.hpp"

LevelComponent::LevelComponent(int width, int height, int tile_size)
	: size(width, height), level(width, height, 0), tile_size(tile_size)
{
}
