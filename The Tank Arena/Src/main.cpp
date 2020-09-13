#include <ctime>

#include "Program.hpp"

int main(int argc, char** argv)
{
	srand(time(NULL));

	Program program;

	program.Init();

	program.MainMenu();

	program.Gameplay();

	return 0;
}