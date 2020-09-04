#pragma once

#include <lic.hpp>

#include "../ProgramUtils.hpp"
#include "Components.hpp"

namespace spawn
{
	void Init(ProgramInfo& program_info, lic::Manager& man);

	lic::Entity Player(
		const lio::Vec2f& pos,
		const lio::Vec2i& hull_size,
		float speed,
		float projectile_speed,
		float turret_interval,
		float projectile_bounce_count,
		uint32_t bullet_count);

	lic::Entity Enemy(
		const lio::Vec2f& pos,
		const lio::Vec2i& hull_size,
		float speed,
		float projectile_speed,
		float turret_interval,
		float projectile_bounce_count,
		uint32_t bullet_count);

	lic::Entity Projectile(
		const lio::Vec2f& start_pos,
		const lio::Vec2f& pos, 
		const lio::Vec2f& init_vel, 
		float speed,
		float decay,
		TurretComponent& turret);
}