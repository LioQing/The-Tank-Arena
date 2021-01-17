#include "MainMenuButtonElement.hpp"

#include "../../../Events.hpp"
#include "../../../Program.hpp"

MainMenuButtonElement::MainMenuButtonElement(const Scale& xscale, uint32_t active_state)
	: ButtonElement(xscale, active_state)
{
}

void MainMenuButtonElement::OnRelease()
{
	lev::Emit<StateChangeEvent>(Program::State::IN_MAIN_MENU);
}