#include "SpriteSystem.hpp"

#include <lic.hpp>

#include "../Components.hpp"
#include "../../ProgramUtils.hpp"

void SpriteSystem::Update()
{
	for (auto [transform, sprite] : manager->Filter<TankTransformComponent, TankSpriteComponent>().Each())
	{
		// position
		sprite.hull_sprite.setPosition(lio::ltosvec<float>(transform.position));
		sprite.turret_sprite.setPosition(lio::ltosvec<float>(transform.position));

		// rotation
		sprite.hull_sprite.setRotation(transform.hull_rotation * 180.0 / M_PI);
		sprite.turret_sprite.setRotation(transform.turret_rotation * 180.0 / M_PI);
	}
}

void SpriteSystem::Draw()
{
	// level sprite
	for (auto& sprite : manager->Filter<LevelSpriteComponent>().Component())
	{
		for (auto& actual_sprite : sprite.tile_sprites)
		{
			program_info->window->draw(actual_sprite);
		}
	}

	// tank sprite
	for (auto& sprite : manager->Filter<TankSpriteComponent>().Component())
	{
		program_info->window->draw(sprite.hull_sprite);
		program_info->window->draw(sprite.turret_sprite);
	}
}
