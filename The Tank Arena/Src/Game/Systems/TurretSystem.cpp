#include "TurretSystem.hpp"

#include <cmath>

#include "../Components.hpp"

void TurretSystem::Update()
{
	for (auto [control, transform] : manager->Filter<PlayerControlComponent, TankTransformComponent>().Each())
	{
		if (control.turret_dir == lio::Vec2f::Zero())
			continue;

		transform.turret_rotation = M_PI / 2 - std::atan2(-control.turret_dir.y, control.turret_dir.x);
	}
}
