#pragma once

#include <atomic>
#include <memory>
#include <LioGraphics.hpp>
#include <lic.hpp>

#include "BaseControlComponent.hpp"

struct AIControlComponent : lic::Component, BaseControlComponent
{
	const float turret_speed;

	std::atomic<std::shared_ptr<lio::Vec2f>> turret_dir;
	std::atomic<std::shared_ptr<lio::Vec2f>> movement;
	std::atomic_bool turret_lock;
	std::atomic_bool fire;

	AIControlComponent(float turret_speed);

	const lio::Vec2f& GetMovement() const override;
	bool TurretLockHull() const override;
};