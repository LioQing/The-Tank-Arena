#include "CollisionSystem.hpp"

#include <cmath>
#include <SFML/Graphics.hpp>
#include <lic.hpp>
#include <LioGraphics.hpp>

#include "../Components.hpp"
#include "../../ProgramUtils.hpp"

CollisionSystem::CollisionSystem(lic::Entity& arena_entity)
	: m_arena_entity(arena_entity)
{
}

void CollisionSystem::Update()
{
	for (auto [collider, transform] : manager->Filter<TankColliderComponent, TankTransformComponent>().Each())
	{
		auto HasNoCollision = [&](const lio::Vec2f& pos) -> bool
		{
			auto& level = m_arena_entity.GetComponent<LevelComponent>();
			for (auto& pos : level.walls)
			{
				for (auto i = 0u; i < 4; ++i)
				{
					auto pt = pos + collider.pts.at(i % 2) * ((i / 2 >= 1) ? -1 : 1) * program_info->scale->Vec2f();
					if (lio::Rect<float>(
						pos * level.tile_size * program_info->scale->Vec2f(),
						program_info->scale->Vec2f() * level.tile_size)
						.Lies(pt))
						return false;
				}
			}
			return true;
		};

		collider.pts.at(0) = (transform.size / 2.f).Rotated(transform.hull_rotation);
		collider.pts.at(1) = (lio::Vec2f(transform.size.x, -transform.size.y) / 2.f).Rotated(transform.hull_rotation);

		auto dir_vec = transform.velocity / transform.velocity.Abs();
		if (std::isnan(dir_vec.x)) dir_vec.x = 0;
		if (std::isnan(dir_vec.y)) dir_vec.y = 0;

		auto& level = m_arena_entity.GetComponent<LevelComponent>();
		for (auto& pos : level.walls)
		{
			for (auto i = 0u; i < 4; ++i)
			{
				auto pt = transform.position + collider.pts.at(i % 2) * ((i / 2 >= 1) ? -1 : 1) * program_info->scale->Vec2f();

				if (!lio::Rect<float>(
					pos * level.tile_size * program_info->scale->Vec2f(),
					program_info->scale->Vec2f() * level.tile_size)
					.Lies(pt))
					continue;

				auto diff = 0.f;
				auto s = 0u;
				auto resolve_vec = lio::Vec2f::Zero();

				// x axis
				if (pos.x - dir_vec.x >= 0 && pos.x - dir_vec.x < level.size.x &&
					!level.level.At(pos.x - dir_vec.x, pos.y))
				{
					for (s = 0u; s != 2; ++s)
					{
						diff = (pos.x + s) * level.tile_size * program_info->scale->Get() - pt.x;
						if (diff / std::abs(diff) == dir_vec.x)
							continue;
						
						resolve_vec.x = diff;
						break;
					}
				}

				// y axis
				if (pos.y - dir_vec.y >= 0 && pos.y - dir_vec.y < level.size.y &&
					!level.level.At(pos.x, pos.y - dir_vec.y))
				{
					for (s = 0u; s != 2; ++s)
					{
						diff = (pos.y + s) * level.tile_size * program_info->scale->Get() - pt.y;
						if (diff / std::abs(diff) == dir_vec.y)
							continue;

						resolve_vec.y = diff;
						break;
					}
				}

				// apply resolve
				if (HasNoCollision(transform.position + lio::Vec2f(resolve_vec.x, 0)) &&
					resolve_vec.x && std::abs(resolve_vec.x) < std::abs(resolve_vec.y))
				{
					transform.position += lio::Vec2f(resolve_vec.x, 0);
					continue;
				}
				if (HasNoCollision(transform.position + lio::Vec2f(0, resolve_vec.y)) &&
					resolve_vec.y && std::abs(resolve_vec.x) > std::abs(resolve_vec.y))
				{
					transform.position += lio::Vec2f(0, resolve_vec.y);
					continue;
				}

				transform.position += resolve_vec;
			}
		}
	}
}

void CollisionSystem::Draw()
{
	// tank collider
	for (auto [collider, transform] : manager->Filter<TankColliderComponent, TankTransformComponent>().Each())
	{
		sf::ConvexShape box(4);
		for (auto i = 0u; i < 4; ++i)
		{
			box.setPoint(i, lio::ltosvec<float>(collider.pts.at(i % 2) * ((i / 2 >= 1) ? -1 : 1))); // to be replaced by coroutine
		}

		box.setPosition(lio::ltosvec<float>(transform.position));
		box.setFillColor(sf::Color::Transparent);
		box.setOutlineColor(sf::Color::Green);
		box.setOutlineThickness(1.f);
		auto perc = 2.f / transform.size;
		box.setScale(lio::ltosvec<float>(program_info->scale->Vec2f() * lio::Vec2f(1.f - perc.x, 1.f - perc.y)));

		program_info->window->draw(box);
	}

	// wall collider
	for (auto& level : manager->Filter<LevelComponent>().Component())
	{
		sf::RectangleShape box(sf::Vector2f(level.tile_size - 1, level.tile_size - 1));

		for (auto& pos : level.walls)
		{
			box.setPosition(lio::ltosvec<float>(pos * level.tile_size * program_info->scale->Vec2f()));
			box.setFillColor(sf::Color::Transparent);
			box.setOutlineColor(sf::Color::Green);
			box.setOutlineThickness(1.f);
			box.setScale(program_info->scale->sfVec2f());

			program_info->window->draw(box);
		}
	}
}