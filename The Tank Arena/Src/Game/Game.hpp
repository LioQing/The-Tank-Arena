#pragma once

#include <lic.hpp>
#include <lev.hpp>
#include <SFML/Graphics.hpp>

#include "Managers.hpp"
#include "../ProgramUtils.hpp"
#include "../GeneralManagers/TextureManager.hpp"

class Game : public lev::Listener
{
private:

	ProgramInfo m_program_info;
	Scale m_scale;

	lic::Manager m_ic_man;
	AIManager m_ai_man;
	ArenaManager m_arena_man;
	SystemManager m_sys_man;
	CameraManager m_cam_man;

public:

	void Init(ProgramInfo program_info, const sf::View& ui_view);
	void Update(float dt);
	void Draw();
	void CleanUp();

	void On(const lev::Event& event) override;
};