#pragma once

#include <memory>
#include <lev.hpp>
#include <SFML/Graphics.hpp>

#include "Game/Game.hpp"
#include "UI/UI.hpp"
#include "ProgramUtils.hpp"
#include "GeneralManagers/TextureManager.hpp"

class Game;
class UI;

class Program : public lev::Listener
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
		IN_MAIN_MENU,
		ENDGAME_MENU,
		LEVEL_MENU
	};

	void Init();
	void Menu();
	void Gameplay();

	TextureManager& TextureManager();
	sf::RenderWindow& Window();
	
	State GetState() const;

	void On(const lev::Event& event) override;

private:

	uint32_t state = State::IN_MAIN_MENU;
	uint32_t level = 0;
};