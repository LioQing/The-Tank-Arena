#include "TurretSystem.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <lev.hpp>

#include "../../ProgramUtils.hpp"
#include "../Components.hpp"
#include "../SpawnEntity.hpp"
#include "../../Events.hpp"

void TurretSystem::Update()
{
	// player turret action
	for (auto [control, transform, turret] : manager->Filter<PlayerControlComponent, TankTransformComponent, TurretComponent>().Each())
	{
		// turret rotation
		if (control.turret_dir != lio::Vec2f::Zero())
			transform.turret_rotation = M_PI / 2 - std::atan2(-control.turret_dir.y, control.turret_dir.x);

		// fire
		if (control.fire && turret.bullet_counter < turret.bullet_count)
		{
			auto adjusted_turret_dir = control.turret_dir * (-1.f, 1.f);
			spawn::Projectile(
				transform.position,
				transform.position + adjusted_turret_dir * 36.f, // radius of turret gun barrel
				adjusted_turret_dir.Normalized(),
				turret.speed,
				turret.bounce_count,
				turret);
			++turret.bullet_counter;
		}
	}

	// ai turret action
	for (auto [control, transform, turret] : manager->Filter<AIControlComponent, TankTransformComponent, TurretComponent>().Each())
	{
		if(transform.GetEntity().HasComponent<HealthComponent>() &&
			transform.GetEntity().GetComponent<HealthComponent>().is_dead)
			continue;

		// turret rotation
		if (*control.turret_dir.load() == lio::Vec2f::Zero() || control.turret_lock.load())
			continue;

		auto target_rot = M_PI / 2 - std::atan2(-control.turret_dir.load()->y, control.turret_dir.load()->x);
		auto diff = lio::rotbound(target_rot - transform.turret_rotation);

		if (std::abs(diff) > std::abs(control.turret_speed * space_time_scale))
			transform.turret_rotation += control.turret_speed * space_time_scale * diff / std::abs(diff);
		else
			transform.turret_rotation = target_rot;
	}
}
