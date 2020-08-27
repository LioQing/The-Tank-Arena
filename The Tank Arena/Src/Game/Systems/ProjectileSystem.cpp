#include "ProjectileSystem.hpp"

#include "../Components.hpp"

void ProjectileSystem::Update()
{
	for (auto& projectile : manager->Filter<ProjectileComponent>().Component())
	{
		if (projectile.bounce_counter >= projectile.bounce_count)
			projectile.GetEntity().Destroy();
	}
}
