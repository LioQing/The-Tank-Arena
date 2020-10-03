#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "Game/Game.hpp"
#include "UI/UI.hpp"
#include "ProgramUtils.hpp"
#include "GeneralManagers/TextureManager.hpp"

class Game;
class UI;

class Program
{
private:

	float delta_time = 0.f;
	sf::Clock delta_clock;

	sf::RenderWindow window;

	TextureManager texture_manager;

	std::shared_ptr<Game> game;
	std::shared_ptr<UI> ui;

public:

	enum State : uint32_t
	{
		CLOSED,
		IN_GAME,
		IN_MAIN_MENU
	};

	void Init();
	void MainMenu();
	void Gameplay();

	TextureManager& TextureManager();
	sf::RenderWindow& Window();
	
	State GetState() const;

private:

	uint32_t state = State::IN_MAIN_MENU;
};