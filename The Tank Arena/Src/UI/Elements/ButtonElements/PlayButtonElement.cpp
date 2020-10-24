#include "PlayButtonElement.hpp"

#include "../../../Events.hpp"
#include "../../../Program.hpp"

PlayButtonElement::PlayButtonElement(const Scale& xscale)
	: ButtonElement(xscale)
{
}

void PlayButtonElement::OnRelease()
{
	lev::Emit<StateChangeEvent>(Program::State::IN_GAME);
}