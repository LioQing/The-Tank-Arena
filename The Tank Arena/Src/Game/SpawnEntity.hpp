#pragma once

#include <lic.hpp>

#include "../ProgramUtils.hpp"
#include "Components.hpp"

namespace spawn
{
	void Init(ProgramInfo& program_info, lic::Manager& man);

	lic::Entity Player(const lio::Vec2f& pos, const std::string& texture_id, const std::string& info_path);

	lic::Entity Enemy(const lio::Vec2f& pos, const std::string& id);

	lic::Entity Projectile(
		const lio::Vec2f& start_pos,
		const lio::Vec2f& pos, 
		const lio::Vec2f& init_vel, 
		float speed,
		float decay,
		TurretComponent& turret);
}