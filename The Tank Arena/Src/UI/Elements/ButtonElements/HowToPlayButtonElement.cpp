#include "HowToPlayButtonElement.hpp"

HowToPlayButtonElement::HowToPlayButtonElement(const Scale& xscale, uint32_t active_state)
	: ButtonElement(xscale, active_state)
{
}

void HowToPlayButtonElement::OnRelease()
{
	std::cout << "There is no how to play yet" << std::endl;
}
