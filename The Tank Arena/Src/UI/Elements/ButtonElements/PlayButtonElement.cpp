#include "PlayButtonElement.hpp"

#include "../../../Program.hpp"

PlayButtonElement::PlayButtonElement(uint32_t* program_state, const Scale& xscale)
	: program_state(program_state), ButtonElement(xscale)
{
}

void PlayButtonElement::OnRelease()
{
	*program_state = Program::State::IN_GAME;
}