#include "ExitButtonElement.hpp"

#include "../../../Events.hpp"
#include "../../../Program.hpp"

ExitButtonElement::ExitButtonElement(const Scale& xscale, uint32_t active_state)
	: ButtonElement(xscale, active_state)
{
}

void ExitButtonElement::OnRelease()
{
	lev::Emit<StateChangeEvent>(Program::State::CLOSED);
}
