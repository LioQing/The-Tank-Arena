#pragma once

#include <LioGraphics.hpp>

struct BaseControlComponent
{
	virtual ~BaseControlComponent() = default;
	virtual const lio::Vec2f& GetMovement() const = 0;
	virtual bool TurretLockHull() const = 0;
};