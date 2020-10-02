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

	// info
	const float window_ui_scale = 200.f; //config

public:

	void Init(ProgramInfo program_info);
	void Update();
	void Draw();

	const sf::View& GetView() const;

	// Main menu

	// Option menu

	// Start game menu

	// Pause game menu

	// End game menu

	void On(const lev::Event& event) override;
};