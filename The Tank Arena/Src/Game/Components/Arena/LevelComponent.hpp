#pragma once

#include <lic.hpp>
#include <Matrix.hpp>
#include <LioGraphics.hpp>

struct LevelComponent : lic::Component
{
	lio::Matrixi level;
	lio::Vec2i size;

	LevelComponent(int width, int height);
};