#pragma once

#include "ButtonElement.hpp"

class ExitButtonElement : public ButtonElement
{
public:

	ExitButtonElement(const Scale& xscale);

	void OnRelease() override;
};