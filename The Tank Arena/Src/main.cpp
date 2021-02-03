#include <ctime>

#include "Program.hpp"
#include "Events.hpp"

int main(int argc, char** argv)
{
	srand(time(NULL));

	Program program;

	program.Init();

	//config
	lev::Emit<UISettingEvent>(
		sf::Color(0x00FF00FF) // crosshair col
		);

	while (program.GetState() != Program::CLOSED)
	{
		switch (program.GetState())
		{
			case Program::IN_MAIN_MENU:
			case Program::ENDGAME_MENU:
			case Program::LEVEL_MENU:
				program.Menu();
				break;

			case Program::IN_GAME:
				program.Gameplay();
				break;
			
			default:
				std::cerr << "Game State Lost" << std::endl;
				break;
		}
	}

	return 0;
}