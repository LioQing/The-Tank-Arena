#pragma once

#include <SFML/Graphics.hpp>

#include "Game/Game.hpp"
#include "UI/UIManager.hpp"

class Program
{
private:

	float delta_time;
	sf::Clock delta_clock;

	sf::RenderWindow window;

	Game game;

	// state of program

public:

	void Init();
	void MainMenu();
	void Gameplay();
};