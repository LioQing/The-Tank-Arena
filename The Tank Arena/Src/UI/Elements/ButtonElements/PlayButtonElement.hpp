#pragma once

#include <SFML/Graphics.hpp>

#include "ButtonElement.hpp"

class PlayButtonElement : public ButtonElement
{
public:

	PlayButtonElement(const Scale& xscale);

	void OnRelease() override;
};