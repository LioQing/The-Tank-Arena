#include "TurretSystem.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <lev.hpp>

#include "../Components.hpp"
#include "../SpawnEntity.hpp"
#include "../../Events.hpp"

void TurretSystem::Update()
{
	// turret action
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
}
