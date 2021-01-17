#pragma once

#include <SFML/Graphics.hpp>

#include "ButtonElement.hpp"

class MainMenuButtonElement : public ButtonElement
{
public:

	MainMenuButtonElement(const Scale& xscale, uint32_t active_state);

	void OnRelease() override;
};