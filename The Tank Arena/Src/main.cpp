#include "Program.hpp"

int main(int argc, char** argv)
{
	Program program;

	program.Init();

	program.MainMenu();

	program.Gameplay();

	return 0;
}