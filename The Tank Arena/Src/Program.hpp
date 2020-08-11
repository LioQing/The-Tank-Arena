#pragma once

#include <SFML/Graphics.hpp>

#include "Game/Game.hpp"
#include "UI/UIManager.hpp"
#include "ProgramUtils/ProgramUtils.hpp"

class Program
{
private:

	float delta_time;
	sf::Clock delta_clock;

	sf::RenderWindow window;
	Scale scale;

	Game game;

	// state of program

public:

	void Init();
	void MainMenu();
	void Gameplay();
};