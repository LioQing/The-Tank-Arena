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
	auto& level = m_arena_entity.GetComponent<LevelComponent>();
	auto bound = level.size * level.tile_size * program_info->scale->Get();

	// tank
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


		// map boundary
		for (auto i = 0u; i < 4; ++i)
		{
			auto pt = transform.position + collider.pts.at(i % 2) * ((i / 2 >= 1) ? -1 : 1) * program_info->scale->Vec2f();

			// x axis
			if (0.f > pt.x)
				transform.position.x += 0.f - pt.x;
			else if (bound.x <= pt.x)
				transform.position.x += bound.x - pt.x;
			
			// y axis
			if (0.f > pt.y)
				transform.position.y += 0.f - pt.y;
			else if (bound.y <= pt.y)
				transform.position.y += bound.y - pt.y;
		}

		// obstacle wall
		for (auto& pos : level.walls)
		{
			for (auto i = 0u; i < 4; ++i)
			{
				auto pt = transform.position + collider.pts.at(i % 2) * ((i / 2 >= 1) ? -1 : 1) * program_info->scale->Vec2f();

				auto dir_vec = pt - transform.position;
				dir_vec /= dir_vec.Abs();

				if (std::isnan(dir_vec.x)) dir_vec.x = 0;
				if (std::isnan(dir_vec.y)) dir_vec.y = 0;

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

	// projectile
	for (auto [projectile, transform] : manager->Filter<ProjectileComponent, ProjectileTransformComponent>().Each())
	{
		auto line = lio::LineSegf(projectile.start_pt, transform.position);

		// map boundary

		// x axis
		if (transform.position.x - transform.radius < 0.f)
			transform.velocity.x = std::abs(transform.velocity.x);
		else if (transform.position.x + transform.radius >= bound.x)
			transform.velocity.x = -1 * std::abs(transform.velocity.x);

		// y axis
		if (transform.position.y - transform.radius < 0.f)
			transform.velocity.y = std::abs(transform.velocity.y);
		else if (transform.position.y + transform.radius >= bound.y)
			transform.velocity.y = -1 * std::abs(transform.velocity.y);
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

	// projectile collider
	for (auto& transform : manager->Filter<ProjectileTransformComponent>().Component())
	{
		sf::CircleShape circle(transform.radius);
		
		circle.setPosition(lio::ltosvec<float>(transform.position - lio::Vec2f(transform.radius, transform.radius) * program_info->scale->Get()));
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineColor(sf::Color::Green);
		circle.setOutlineThickness(1.f);
		circle.setScale(program_info->scale->sfVec2f());

		program_info->window->draw(circle);
	}
}
