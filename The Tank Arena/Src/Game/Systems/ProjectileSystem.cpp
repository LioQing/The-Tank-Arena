#include "ProjectileSystem.hpp"

#include "../Components.hpp"

void ProjectileSystem::Update()
{
	for (auto& projectile : manager->Filter<ProjectileComponent>().Component())
	{
		projectile.decay_timer += dt;

		if (projectile.decay_timer > projectile.decay)
			projectile.GetEntity().Destroy();
	}
}
