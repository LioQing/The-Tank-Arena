#pragma once

#include <lic.hpp>

#include "Managers/AIManager.hpp"
#include "Managers/ArenaManager.hpp"

class Game
{
private:

	lic::Manager m_ic_man;
	AIManager m_ai_man;
	ArenaManager m_arena_man;

	// list of systems for updates

	// state of game (for communication with other managers)

public:

	void Init();
	void Update();
	void CleanUp();
};