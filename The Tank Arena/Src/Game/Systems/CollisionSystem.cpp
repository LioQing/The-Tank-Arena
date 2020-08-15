#include "CollisionSystem.hpp"

#include <SFML/Graphics.hpp>
#include <lic.hpp>

#include "../Components.hpp"
#include "../../ProgramUtils.hpp"

void CollisionSystem::Update()
{
	for (auto [collider, transform] : manager->Filter<TankColliderComponent, TankTransformComponent>().Each())
	{
		collider.pts.at(0) = (transform.size / 2.f).Rotated(transform.hull_rotation);
		collider.pts.at(1) = (lio::Vec2f(transform.size.x, -transform.size.y) / 2.f).Rotated(transform.hull_rotation);
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
