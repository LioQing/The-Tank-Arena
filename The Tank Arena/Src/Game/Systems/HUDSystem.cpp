#include "HUDSystem.hpp"

#include <cmath>

#include "../../Events.hpp"
#include "../Components.hpp"

HUDSystem::HUDSystem(lic::Entity& arena_entity)
	: arena_entity(arena_entity)
{
	Listen<GameSettingEvent>();
	Listen<UISettingEvent>();
}

void HUDSystem::Update()
{
	for (auto [control, transform] : manager->Filter<PlayerControlComponent, TankTransformComponent>().Each())
	{
		auto& hud = arena_entity.GetComponent<HUDComponent>();
		hud.crosshair_line.setPosition(lio::ltosvec<float>(transform.position));
		hud.crosshair_line.setSize(sf::Vector2f(transform.position.Distance(hud.crosshair_pos), 0.f));
		hud.crosshair_line.setRotation(std::atan2(hud.crosshair_pos.y - transform.position.y, hud.crosshair_pos.x - transform.position.x) * 180 / M_PI);
	}
}

void HUDSystem::Draw()
{
}

void HUDSystem::On(const lev::Event& event)
{
	if (event.Is<GameSettingEvent>())
	{
		auto& hud = arena_entity.GetComponent<HUDComponent>();
		const auto& game_setting = static_cast<const GameSettingEvent&>(event);

		hud.crosshair_line.setOutlineColor(game_setting.crosshair_line_col);
		hud.crosshair_line.setOutlineThickness(game_setting.crosshair_line_thickness);
	}
}
