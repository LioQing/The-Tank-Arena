#include "EndGameSystem.hpp"

#include "../../Events.hpp"
#include "../../Program.hpp"
#include "../Components.hpp"

void EndGameSystem::Update()
{
	for (auto& end_game : manager->Filter<EndGameComponent>().Component())
	{
		if (end_game.is_ended)
		{
			end_game.timer += dt;
		}

		if (end_game.timer >= end_game.countdown)
		{
			lev::Emit<StateChangeEvent>(Program::State::IN_MAIN_MENU);
		}
	}
}
