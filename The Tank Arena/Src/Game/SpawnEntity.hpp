#pragma once

#include <lic.hpp>

#include "../ProgramUtils.hpp"

namespace spawn
{
	void Init(ProgramInfo& program_info, lic::Manager& man);

	lic::Entity Player(
		const lio::Vec2f& pos,
		const lio::Vec2i& hull_size,
		float speed,
		float projectile_speed,
		float turret_interval,
		float projectile_bounce_count);

	lic::Entity Enemy(
		const lio::Vec2f& pos,
		const lio::Vec2i& hull_size);

	lic::Entity Projectile(
		const lio::Vec2f& start_pos,
		const lio::Vec2f& pos, 
		const lio::Vec2f& init_vel, 
		float speed,
		float decay);
}