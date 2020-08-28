#include "SpriteSystem.hpp"

#include <lic.hpp>

#include "../Components.hpp"
#include "../Events.hpp"
#include "../../Events.hpp"
#include "../../ProgramUtils.hpp"

SpriteSystem::SpriteSystem()
{
	Listen<GameSettingEvent>();
	Listen<SpriteRescaleEvent>();
}

void SpriteSystem::Update()
{
	// tank
	for (auto [transform, sprite] : manager->Filter<TankTransformComponent, TankSpriteComponent>().Each())
	{
		// position
		sprite.hull_sprite.setPosition(lio::ltosvec<float>(transform.position));
		sprite.turret_sprite.setPosition(lio::ltosvec<float>(transform.position));

		// rotation
		sprite.hull_sprite.setRotation(transform.hull_rotation * 180.0 / M_PI);
		sprite.turret_sprite.setRotation(transform.turret_rotation * 180.0 / M_PI);
	}

	// proj
	for (auto [transform, sprite] : manager->Filter<ProjectileTransformComponent, ProjectileSpriteComponent>().Each())
	{
		sprite.sprite.setPosition(lio::ltosvec<float>(transform.position));
	}
}

void SpriteSystem::Draw()
{
	auto view_bound = sf::FloatRect{
		program_info->window->getView().getCenter().x - program_info->window->getView().getSize().x / 2.f,
		program_info->window->getView().getCenter().y - program_info->window->getView().getSize().y / 2.f,
		program_info->window->getView().getSize().x,
		program_info->window->getView().getSize().y
	};

	// level sprite
	for (auto& sprite : manager->Filter<LevelSpriteComponent>().Component())
	{
		for (auto& actual_sprite : sprite.tile_sprites)
		{
			if (!lio::inview(actual_sprite.getGlobalBounds(), view_bound))
				continue;

			program_info->window->draw(actual_sprite);
		}
	}

	// crosshair line
	for (auto& hud : manager->Filter<HUDComponent>().Component())
	{
		program_info->window->draw(hud.crosshair_line);
	}

	// tank sprite
	for (auto& sprite : manager->Filter<TankSpriteComponent>().Component())
	{
		if (!lio::inview(sprite.hull_sprite.getGlobalBounds(), view_bound))
			continue;

		program_info->window->draw(sprite.hull_sprite);
		program_info->window->draw(sprite.turret_sprite);
	}

	// proj sprite
	for (auto& sprite : manager->Filter<ProjectileSpriteComponent>().Component())
	{
		if (!lio::inview(sprite.sprite.getGlobalBounds(), view_bound))
			continue;

		program_info->window->draw(sprite.sprite);
	}
}

void SpriteSystem::On(const lev::Event& event)
{
	if (event.Is<SpriteRescaleEvent>())
	{
		const auto& ev = static_cast<const SpriteRescaleEvent&>(event);
		auto rescale = ev.current_scale.Get() / ev.previous_scale.Get();

		// level sprite
		for (auto [level, sprite] : manager->Filter<LevelComponent, LevelSpriteComponent>().Each())
		{
			for (auto y = 0u; y < level.level.height; ++y)
			{
				for (auto x = 0u; x < level.level.width; ++x)
				{
					auto& tile_sprite = sprite.tile_sprites.at(y * level.level.width + x);
					tile_sprite.setPosition(tile_sprite.getPosition().x * rescale, tile_sprite.getPosition().y * rescale);
					tile_sprite.setScale(ev.current_scale.sfVec2f());
				}
			}
		}

		// tank sprite
		for (auto [transform, sprite] : manager->Filter<TankTransformComponent, TankSpriteComponent>().Each())
		{
			sprite.hull_sprite.setScale(ev.current_scale.sfVec2f());
			sprite.turret_sprite.setScale(ev.current_scale.sfVec2f());
			transform.position *= rescale;
		}

		// proj sprite
		for (auto [transform, sprite] : manager->Filter<ProjectileTransformComponent, ProjectileSpriteComponent>().Each())
		{
			sprite.sprite.setScale((ev.current_scale).sfVec2f());
			transform.position *= rescale;
		}
	}
	else if (event.Is<GameSettingEvent>())
	{
		const auto& game_setting = static_cast<const GameSettingEvent&>(event);

		for (auto [control, sprite] : manager->Filter<PlayerControlComponent, TankSpriteComponent>().Each())
		{
			sprite.hull_sprite.setColor(game_setting.tank_col);
			sprite.turret_sprite.setColor(game_setting.tank_col);
		}
	}
}
