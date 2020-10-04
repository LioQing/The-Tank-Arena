#pragma once

#include "ButtonElement.hpp"

class ExitButtonElement : public ButtonElement
{
private:

	uint32_t* program_state = nullptr;

public:

	ExitButtonElement(uint32_t* program_state, const Scale& xscale);

	void OnRelease() override;
};