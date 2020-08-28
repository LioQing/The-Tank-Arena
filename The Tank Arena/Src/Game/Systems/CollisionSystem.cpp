#include "CollisionSystem.hpp"

#include <cmath>
#include <SFML/Graphics.hpp>
#include <lic.hpp>
#include <LioGraphics.hpp>

#include "../Components.hpp"
#include "../../ProgramUtils.hpp"

CollisionSystem::CollisionSystem(const lic::Entity& arena_entity)
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
		for (auto& edge : level.edge_pool)
		{
			auto edgef = edge.edge * level.tile_size * program_info->scale->Get();

			lio::Vec2f pts[2];
			pts[0] = transform.position + collider.pts.at(1) * -1 * program_info->scale->Vec2f();
			auto resolve = lio::Vec2f::Zero();

			for (auto i = 0u; i < 4; ++i)
			{
				pts[1] = transform.position + collider.pts.at(i % 2) * ((i / 2 >= 1) ? -1 : 1) * program_info->scale->Vec2f();

				if (edgef.Intersect(lio::LineSegf(pts[0], pts[1])))
				{
					for (auto j = 0u; j < 2; ++j)
					{
						if (edge.dir == Dir::LEFT && pts[j].x < edgef.p1.x ||
							edge.dir == Dir::RIGHT && pts[j].x > edgef.p1.x)
						{
							if (std::abs(edgef.p1.x - pts[j].x) > std::abs(resolve.x))
							{
								resolve.x = edgef.p1.x - pts[j].x;
								break;
							}
						}
						else if (edge.dir == Dir::UP && pts[j].y < edgef.p1.y ||
							edge.dir == Dir::DOWN && pts[j].y > edgef.p1.y)
						{
							if (std::abs(edgef.p1.y - pts[j].y) > std::abs(resolve.y))
							{
								resolve.y = edgef.p1.y - pts[j].y;
								break;
							}
						}
					}
					break;
				}

				pts[0] = pts[1];
			}

			transform.position += resolve;
		}
	}

	// projectile
	for (auto [projectile, transform] : manager->Filter<ProjectileComponent, ProjectileTransformComponent>().Each())
	{
		auto proj_line = lio::LineSegf(projectile.start_pt, transform.position);

		// map boundary
		auto hit_bound = false;

		// x axis
		if (transform.position.x - transform.radius < 0.f)
		{
			transform.velocity.x = std::abs(transform.velocity.x);
			hit_bound = true;
		}
		else if (transform.position.x + transform.radius >= bound.x)
		{
			transform.velocity.x = -1 * std::abs(transform.velocity.x);
			hit_bound = true;
		}

		// y axis
		if (transform.position.y - transform.radius < 0.f)
		{
			transform.velocity.y = std::abs(transform.velocity.y);
			hit_bound = true;
		}
		else if (transform.position.y + transform.radius >= bound.y)
		{
			transform.velocity.y = -1 * std::abs(transform.velocity.y);
			hit_bound = true;
		}

		if (hit_bound)
		{
			projectile.start_pt = transform.position;
			++projectile.bounce_counter;
		}

		// obstacle wall
		for (auto& edge : level.edge_pool)
		{
			auto edgef = (edge.edge * level.tile_size - Dir::DirToVec(edge.dir) * transform.radius) * program_info->scale->Get();

			std::pair<double*, double*> pts;
			if (edge.dir == Dir::LEFT || edge.dir == Dir::RIGHT)
				pts = std::make_pair(&edgef.p1.y, &edgef.p2.y);
			else
				pts = std::make_pair(&edgef.p1.x, &edgef.p2.x);

			*pts.first -= transform.radius * program_info->scale->Get();
			*pts.second += transform.radius * program_info->scale->Get();

			if (!edgef.Intersect(proj_line))
				continue;

			auto contact_pt = edgef.IntersectPt(proj_line);

			projectile.start_pt = contact_pt - Dir::DirToVec(edge.dir);
			transform.position = contact_pt - Dir::DirToVec(edge.dir);
			transform.velocity *= (edge.dir == Dir::UP || edge.dir == Dir::DOWN) ? lio::Vec2(1, -1) : lio::Vec2(-1, 1);
			++projectile.bounce_counter;
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
			box.setPoint(i, lio::ltosvec<float>(collider.pts.at(i % 2) * ((i / 2 >= 1) ? -1 : 1)));
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
	{
		auto& level = m_arena_entity.GetComponent<LevelComponent>();
		sf::RectangleShape box;

		for (const auto& line : level.edge_pool)
		{
			auto tmp = lio::LineSegi(line.edge.p1 * lio::Vec2i::Left(), line.edge.p2 * lio::Vec2i::Left());

			box.setPosition(lio::ltosvec<float>(line.edge.p1 * level.tile_size * program_info->scale->Vec2f()));
			box.setSize(lio::ltosvec<float>((line.edge.p2 - line.edge.p1) * level.tile_size));
			box.setFillColor(sf::Color::Transparent);

			switch (line.dir)
			{
				case Dir::DOWN:
					box.setOutlineColor(sf::Color::Green);
					break;

				case Dir::UP:
					box.setOutlineColor(sf::Color::Red);
					break;

				case Dir::LEFT:
					box.setOutlineColor(sf::Color::Blue);
					break;

				default:
					box.setOutlineColor(sf::Color::Black);
					break;
			}
			
			box.setOutlineThickness(.5f);
			box.setScale(program_info->scale->sfVec2f());

			program_info->window->draw(box);
		}
	}

	// projectile collider
	for (const auto& transform : manager->Filter<ProjectileTransformComponent>().Component())
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
