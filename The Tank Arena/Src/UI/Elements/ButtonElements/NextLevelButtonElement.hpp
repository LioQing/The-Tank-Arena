#pragma once

#include <SFML/Graphics.hpp>

#include "ButtonElement.hpp"

class NextLevelButtonElement : public ButtonElement
{
public:

	NextLevelButtonElement(const Scale& xscale, uint32_t active_state);

	void OnRelease() override;
};