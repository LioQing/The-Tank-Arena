#include "EndGameSystem.hpp"

#include "../../Program.hpp"
#include "../Components.hpp"

EndGameSystem::EndGameSystem(uint32_t* program_state)
	: program_state(program_state)
{
}

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
			*program_state = Program::State::IN_MAIN_MENU;
		}
	}
}
