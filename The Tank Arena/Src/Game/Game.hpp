#pragma once

#include <lic.hpp>
#include <SFML/Graphics.hpp>

#include "Managers/AIManager.hpp"
#include "Managers/ArenaManager.hpp"
#include "../GeneralManagers/TextureManager.hpp"
#include "../ProgramUtils/ProgramUtils.hpp"

class Game
{
private:

	sf::RenderWindow* m_window = nullptr;
	Scale* m_scale;

	lic::Manager m_ic_man;
	AIManager m_ai_man;
	ArenaManager m_arena_man;
	TextureManager m_tex_man;

	// list of systems for updates

	// state of game (for communication with other managers)

public:

	Game() = default;

	void Init(sf::RenderWindow* window, Scale* scale);
	void Update(float dt);
	void Draw();
	void CleanUp();
};