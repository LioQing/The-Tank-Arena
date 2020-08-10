#pragma once

#include <lic.hpp>
#include <SFML/Graphics.hpp>

#include "Managers/AIManager.hpp"
#include "Managers/ArenaManager.hpp"

class Game
{
private:

	sf::RenderWindow* m_window;

	lic::Manager m_ic_man;
	AIManager m_ai_man;
	ArenaManager m_arena_man;

	// list of systems for updates

	// state of game (for communication with other managers)

public:

	Game() = default;
	Game(sf::RenderWindow& window);

	void Init(sf::RenderWindow* window);
	void Update(float dt);
	void Draw();
	void CleanUp();
};