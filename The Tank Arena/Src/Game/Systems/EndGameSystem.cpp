#include "EndGameSystem.hpp"

#include "../../UI/Events.hpp"
#include "../../Events.hpp"
#include "../../Program.hpp"
#include "../Components.hpp"

EndGameSystem::EndGameSystem(lic::Entity& arena_entity)
	: arena_entity(arena_entity)
{
}

void EndGameSystem::Update()
{
	auto& end_game = arena_entity.GetComponent<EndGameComponent>();

	for (auto [player, health] : manager->Filter<PlayerControlComponent, HealthComponent>().Each())
	{
		if (health.is_dead)
			end_game.is_ended = true;
	}

	if (end_game.is_ended)
	{
		end_game.timer += dt;
	}
	else
	{
		lev::Emit<TimerEvent>(dt);
	}

	if (end_game.timer >= end_game.countdown)
	{
		lev::Emit<StateChangeEvent>(Program::State::ENDGAME_MENU);

		const auto& game_stat = arena_entity.GetComponent<GameStatsComponent>();
		lev::Emit<StatDisplayEvent>(game_stat.tank_destroyed, game_stat.bullet_fired);
	}
}
