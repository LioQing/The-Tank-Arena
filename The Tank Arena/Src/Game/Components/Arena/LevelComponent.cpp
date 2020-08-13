#include "LevelComponent.hpp"

LevelComponent::LevelComponent(int width, int height)
	: size(width, height), level(width, height, 0)
{
}
