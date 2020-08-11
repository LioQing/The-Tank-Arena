#pragma once

#include <SFML/Graphics.hpp>

#include "Game/Game.hpp"
#include "UI/UIManager.hpp"
#include "ProgramUtils.hpp"
#include "GeneralManagers/TextureManager.hpp"

class Program
{
private:

	float delta_time = 0.f;
	sf::Clock delta_clock;

	sf::RenderWindow window;
	Scale scale;

	TextureManager texture_manager;

	Game game;

	// state of program

public:

	void Init();
	void MainMenu();
	void Gameplay();

	TextureManager& TextureManager();
	sf::RenderWindow& Window();
};