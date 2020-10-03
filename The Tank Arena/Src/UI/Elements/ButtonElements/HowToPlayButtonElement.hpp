#pragma once

#include "ButtonElement.hpp"

class HowToPlayButtonElement : public ButtonElement
{
public:

	HowToPlayButtonElement(const Scale& xscale);

	void OnRelease() override;
};