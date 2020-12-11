#include "ProjectileSystem.hpp"

#include "../Components.hpp"

void ProjectileSystem::Update()
{
	for (auto& projectile : manager->Filter<ProjectileComponent>().Component())
	{
		if (projectile.bounce_counter >= projectile.bounce_count && !projectile.hit)
		{
			--projectile.turret.bullet_counter;
			projectile.hit = true;
			projectile.GetEntity().GetComponent<ProjectileSpriteComponent>().sprite.setTexture(*program_info->texture_manager->GetTexture("explode"));
		}

		if (projectile.hit)
		{
			projectile.anim_timer += dt;
		}

		if (projectile.anim_timer >= projectile.anim_time)
		{
			projectile.GetEntity().Destroy();
		}
	}
}
