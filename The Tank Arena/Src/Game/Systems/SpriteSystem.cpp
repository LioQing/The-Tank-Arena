#include "SpriteSystem.hpp"

#include <lic.hpp>

#include "../Components.hpp"
#include "../../ProgramUtils.hpp"

void SpriteSystem::Update()
{
	for (auto [transform, sprite] : manager->Filter<TankTransformComponent, TankSpriteComponent>().Each())
	{
		sprite.hull_sprite.setPosition(ltos::ToSFVec<float>(transform.position));
		sprite.turret_sprite.setPosition(ltos::ToSFVec<float>(transform.position));
	}
}

void SpriteSystem::Draw()
{
	for (auto& sprite : manager->Filter<TankSpriteComponent>().Component())
	{
		program_info->window->draw(sprite.hull_sprite);
		program_info->window->draw(sprite.turret_sprite);
	}
}
