#include <ctime>

#include "Program.hpp"

int main(int argc, char** argv)
{
	srand(time(NULL));

	Program program;

	program.Init();

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
		}
	}

	return 0;
}