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
				program.MainMenu();
				break;

			case Program::IN_GAME:
				program.Gameplay();
				break;

			case Program::ENDGAME_MENU:
				program.Endgame();
				break;
		}
	}

	return 0;
}