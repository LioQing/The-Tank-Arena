#pragma once

#include <SFML/Graphics.hpp>

#include "ButtonElement.hpp"

class RetryButtonElement : public ButtonElement
{
public:

	RetryButtonElement(const Scale& xscale, uint32_t active_state);

	void OnRelease() override;
};