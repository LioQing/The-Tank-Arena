#pragma once

#include <SFML/Graphics.hpp>

#include "ButtonElement.hpp"

class PlayButtonElement : public ButtonElement
{
public:

	PlayButtonElement(const Scale& xscale, uint32_t active_state);

	void OnRelease() override;
};