#include "PlayButtonElement.hpp"

#include "../../../Events.hpp"
#include "../../../Program.hpp"

PlayButtonElement::PlayButtonElement(const Scale& xscale, uint32_t active_state)
	: ButtonElement(xscale, active_state)
{
}

void PlayButtonElement::OnRelease()
{
	lev::Emit<StateChangeEvent>(Program::State::LEVEL_MENU);
}