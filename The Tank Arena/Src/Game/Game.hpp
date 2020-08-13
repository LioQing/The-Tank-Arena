#pragma once

#include <lic.hpp>
#include <SFML/Graphics.hpp>

#include "Managers.hpp"
#include "../ProgramUtils.hpp"
#include "../GeneralManagers/TextureManager.hpp"

class Game
{
private:

	ProgramInfo m_program_info;
	Scale m_scale;

	lic::Manager m_ic_man;
	AIManager m_ai_man;
	ArenaManager m_arena_man;
	SystemManager m_sys_man;
	CameraManager m_cam_man;

	// state of game (for communication with other managers)

public:

	void Init(ProgramInfo program_info);
	void Update(float dt);
	void Draw();
	void CleanUp();
};