#pragma once

#include <SFML/Graphics.hpp>

#include "ButtonElement.hpp"

class PlayButtonElement : public ButtonElement
{
private:

	uint32_t* program_state = nullptr;

public:

	PlayButtonElement(uint32_t* program_state, const Scale& xscale);

	void OnRelease() override;
};