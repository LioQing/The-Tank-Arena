#pragma once

#include "ButtonElement.hpp"

class HowToPlayButtonElement : public ButtonElement
{
public:

	HowToPlayButtonElement(const Scale& xscale, uint32_t active_state);

	void OnRelease() override;
};