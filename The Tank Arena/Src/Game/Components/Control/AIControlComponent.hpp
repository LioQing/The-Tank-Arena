#pragma once

#include <atomic>
#include <memory>
#include <LioGraphics.hpp>
#include <lic.hpp>

struct AIControlComponent : lic::Component
{
	const float turret_speed;

	std::atomic<std::shared_ptr<lio::Vec2f>> turret_dir;

	AIControlComponent(float turret_speed);
};