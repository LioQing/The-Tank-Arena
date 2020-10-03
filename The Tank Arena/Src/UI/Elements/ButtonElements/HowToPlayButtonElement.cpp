#include "HowToPlayButtonElement.hpp"

HowToPlayButtonElement::HowToPlayButtonElement(const Scale& xscale)
	: ButtonElement(xscale)
{
}

void HowToPlayButtonElement::OnRelease()
{
	std::cout << "There is no how to play yet" << std::endl;
}
