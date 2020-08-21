#include "TurretSystem.hpp"

#include <cmath>

#include "../Components.hpp"
#include "../SpawnEntity.hpp"

void TurretSystem::Update()
{
	for (auto [control, transform, turret] : manager->Filter<PlayerControlComponent, TankTransformComponent, TurretComponent>().Each())
	{
		// turret rotation
		if (control.turret_dir != lio::Vec2f::Zero())
			transform.turret_rotation = M_PI / 2 - std::atan2(-control.turret_dir.y, control.turret_dir.x);

		// fire
		if (control.fire)
		{
			auto adjusted_turret_dir = control.turret_dir * (-1.f, 1.f);
			spawn::Projectile(
				transform.position + adjusted_turret_dir * 36.f,
				adjusted_turret_dir.Normalized(),
				turret.speed,
				turret.decay);
		}
	}
}
