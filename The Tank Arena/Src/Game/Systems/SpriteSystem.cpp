#include "SpriteSystem.hpp"

#include <lic.hpp>

#include "../Components.hpp"

void SpriteSystem::Update()
{
	for (auto& sprite : manager->Filter<TankSpriteComponent>().Component())
	{
		program_info->window->draw(sprite.hull_sprite);
		program_info->window->draw(sprite.turret_sprite);
	}
}
