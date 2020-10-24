#include "ExitButtonElement.hpp"

#include "../../../Events.hpp"
#include "../../../Program.hpp"

ExitButtonElement::ExitButtonElement(const Scale& xscale)
	: ButtonElement(xscale)
{
}

void ExitButtonElement::OnRelease()
{
	lev::Emit<StateChangeEvent>(Program::State::CLOSED);
}
