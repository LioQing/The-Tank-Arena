#pragma once

#include <atomic>
#include <memory>
#include <LioGraphics.hpp>
#include <lic.hpp>

struct AIControlComponent : lic::Component
{
	std::atomic<std::shared_ptr<lio::Vec2f>> turret_dir;

	AIControlComponent();
};