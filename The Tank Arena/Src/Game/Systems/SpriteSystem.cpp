#include "SpriteSystem.hpp"

#include <lic.hpp>

#include "../Components.hpp"
#include "../Events.hpp"
#include "../../ProgramUtils.hpp"

SpriteSystem::SpriteSystem()
{
	Listen<WindowResizedEvent>();
}

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

void SpriteSystem::On(const lev::Event& event)
{
	if (event.Is<WindowResizedEvent>())
	{
		const auto& wr_ev = static_cast<const WindowResizedEvent&>(event);
		auto rescale = wr_ev.current_scale.Get() / wr_ev.previous_scale.Get();

		// level sprite
		for (auto [level, sprite] : manager->Filter<LevelComponent, LevelSpriteComponent>().Each())
		{
			for (auto y = 0u; y < level.level.height; ++y)
			{
				for (auto x = 0u; x < level.level.width; ++x)
				{
					auto& tile_sprite = sprite.tile_sprites.at(y * level.level.width + x);
					tile_sprite.setPosition(tile_sprite.getPosition().x * rescale, tile_sprite.getPosition().y * rescale);
					tile_sprite.setScale(wr_ev.current_scale.sfVec2f());
				}
			}
		}

		// tank sprite
		for (auto [transform, sprite] : manager->Filter<TankTransformComponent, TankSpriteComponent>().Each())
		{
			sprite.hull_sprite.setScale((wr_ev.current_scale * .5f).sfVec2f());
			sprite.turret_sprite.setScale((wr_ev.current_scale * .5f).sfVec2f());
			transform.position *= rescale;
		}
	}
}