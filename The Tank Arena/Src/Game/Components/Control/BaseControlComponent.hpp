#pragma once

#include <LioGraphics.hpp>

struct BaseControlComponent
{
	virtual ~BaseControlComponent() = default;
	virtual const lio::Vec2f& GetMovement() const = 0;
};