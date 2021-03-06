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
		// tex rect
		if (transform.GetEntity().HasComponent<HealthComponent>())
		{
			const auto& health = transform.GetEntity().GetComponent<HealthComponent>();

			sprite.hull_sprite.setTextureRect(sf::IntRect{ sprite.tex_rect_size * health.is_dead, 0, sprite.tex_rect_size, sprite.tex_rect_size });
			sprite.turret_sprite.setTextureRect(sf::IntRect{ sprite.tex_rect_size * health.is_dead, 0, sprite.tex_rect_size, sprite.tex_rect_size });
		}

		// position
		sprite.hull_sprite.setPosition(lio::ltosvec<float>(transform.position));
		sprite.turret_sprite.setPosition(lio::ltosvec<float>(transform.position));

		// rotation
		sprite.hull_sprite.setRotation(transform.hull_rotation * 180.0 / M_PI);
		sprite.turret_sprite.setRotation(transform.turret_rotation * 180.0 / M_PI);
	}

	// proj
	for (auto [projectile, transform, sprite] : manager->Filter<ProjectileComponent, ProjectileTransformComponent, ProjectileSpriteComponent>().Each())
	{
		if (projectile.hit)
			continue;

		sprite.sprite.setPosition(lio::ltosvec<float>(transform.position));
	}

	// gunfire
	for (auto& gunfire : manager->Filter<GunfireSpriteComponent>().Component())
	{
		gunfire.timer -= dt;

		if (gunfire.timer <= 0.f)
			gunfire.GetEntity().Destroy();
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

	// gunfire sprite
	for (auto& sprite : manager->Filter<GunfireSpriteComponent>().Component())
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

		// gunfire sprite
		for (auto& gunfire : manager->Filter<GunfireSpriteComponent>().Component())
		{
			gunfire.sprite.setScale(ev.current_scale.sfVec2f());
			gunfire.sprite.setPosition(gunfire.sprite.getPosition().x * rescale, gunfire.sprite.getPosition().y * rescale);
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
