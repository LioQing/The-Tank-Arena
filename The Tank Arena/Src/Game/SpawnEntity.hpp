#pragma once

#include <lic.hpp>

#include "../ProgramUtils.hpp"

namespace spawn
{
	void Init(ProgramInfo& program_info, lic::Manager& man);

	lic::Entity Player();
	lic::Entity Projectile(const lio::Vec2f& pos, const lio::Vec2f& init_vel);
}