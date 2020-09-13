#pragma once

#include <lic.hpp>
#include <LioGraphics.hpp>

#include "BaseControlComponent.hpp"

struct PlayerControlComponent : lic::Component, BaseControlComponent
{
	lio::Vec2f movement;
	lio::Vec2f turret_dir;
	bool fire;
	bool is_joystick = false;

	PlayerControlComponent();

	const lio::Vec2f& GetMovement() const override;
	bool TurretLockHull() const override;
};