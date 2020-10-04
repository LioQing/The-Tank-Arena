#include "ExitButtonElement.hpp"

#include "../../../Program.hpp"

ExitButtonElement::ExitButtonElement(uint32_t* program_state, const Scale& xscale)
	: program_state(program_state), ButtonElement(xscale)
{
}

void ExitButtonElement::OnRelease()
{
	*program_state = Program::State::CLOSED;
}
