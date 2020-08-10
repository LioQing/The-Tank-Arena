#include "Program.hpp"

Program program;

int main(int argc, char** argv)
{
	program.Init();

	program.MainMenu();

	program.Gameplay();

	return 0;
}