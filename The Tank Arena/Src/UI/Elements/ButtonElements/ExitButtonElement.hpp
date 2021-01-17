#pragma once

#include "ButtonElement.hpp"

class ExitButtonElement : public ButtonElement
{
public:

	ExitButtonElement(const Scale& xscale, uint32_t active_state);

	void OnRelease() override;
};