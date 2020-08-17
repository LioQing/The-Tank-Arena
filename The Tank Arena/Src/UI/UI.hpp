#pragma once

#include <lev.hpp>
#include <SFML/Graphics.hpp>

#include "Managers.hpp"
#include "../ProgramUtils.hpp"

class UI : public lev::Listener
{
private:

	// state
	ProgramInfo m_program_info;
	Scale m_scale;
	sf::View m_view;

	// managers
	ElementManager element_man;

public:

	void Init(ProgramInfo program_info);
	void Update();
	void Draw();

	// Main menu

	// Option menu

	// Start game menu

	// Pause game menu

	// End game menu

	void On(const lev::Event& event) override;
};