#include "CrosshairSystem.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <lev.hpp>

#include "../Components.hpp"
#include "../../Events.hpp"

CrosshairSystem::CrosshairSystem(lic::Entity& arena_entity)
	: arena_entity(arena_entity)
{
}

void CrosshairSystem::Update()
{
	auto& level = arena_entity.GetComponent<LevelComponent>();

	// cursor / cross hair
	const auto view = program_info->window->getView();
	program_info->window->setView(program_info->window->getDefaultView());
	auto pos = program_info->window->mapPixelToCoords(sf::Mouse::getPosition(*program_info->window));
	program_info->window->setView(view);
	arena_entity.GetComponent<HUDComponent>().crosshair_pos = lio::stolvec<float>(program_info->window->mapPixelToCoords(sf::Mouse::getPosition(*program_info->window)));

	const auto max_distance = lio::stolvec<float>(view.getSize()).Magnitude();
	for (auto& control : manager->Filter<PlayerControlComponent>().Component())
	{
		if (!control.is_joystick)
			break;

		auto& transform = control.GetEntity().GetComponent<TankTransformComponent>();
		auto adjusted_rot = M_PI / 2 - transform.turret_rotation;

		auto min_view_line = lio::LineSegf(transform.position + lio::Vec2f(std::cos(adjusted_rot), -std::sin(adjusted_rot)) * max_distance, transform.position);

		// obstacle wall
		for (auto& edge : level.edge_pool)
		{
			auto edgef = edge.edge * level.tile_size * program_info->scale->Get();
			//edgef is calculated so many times that it could be a const

			if (!edgef.Intersect(min_view_line))
				continue;

			min_view_line.p1 = edgef.IntersectPt(min_view_line);
		}

		// map boundary
		auto scaled_map_size = level.size * level.tile_size * program_info->scale->Get();

		if (min_view_line.p1.x > scaled_map_size.x)
			min_view_line.p1 = lio::LineSegf(scaled_map_size, lio::Vec2f(scaled_map_size.x, 0)).IntersectPt(min_view_line);
		else if (min_view_line.p1.x < 0.f)
			min_view_line.p1 = lio::LineSegf(lio::Vec2f::Zero(), lio::Vec2f(0, scaled_map_size.y)).IntersectPt(min_view_line);
		
		if (min_view_line.p1.y > scaled_map_size.y)
			min_view_line.p1 = lio::LineSegf(scaled_map_size, lio::Vec2f(0, scaled_map_size.y)).IntersectPt(min_view_line);
		else if (min_view_line.p1.y < 0.f)
			min_view_line.p1 = lio::LineSegf(lio::Vec2f::Zero(), lio::Vec2f(scaled_map_size.x, 0)).IntersectPt(min_view_line);

		pos = lio::ltosvec<float>(min_view_line.p1
			+ lio::stolvec<float>(view.getSize()) / 2.f
			- lio::stolvec<float>(view.getCenter()));

		arena_entity.GetComponent<HUDComponent>().crosshair_pos = min_view_line.p1;
	}

	lev::Emit<InGameCursorEvent>(pos);
}
