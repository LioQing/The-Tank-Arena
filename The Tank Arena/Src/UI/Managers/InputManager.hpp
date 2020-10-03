#pragma once

#include <vector>
#include <lev.hpp>

#include "../Elements/ButtonElements/ButtonElement.hpp"

class ButtonElement;

class InputManager : public lev::Listener
{
private:

	std::vector<ButtonElement*> buttons;

public:

	InputManager();

	void AddButton(ButtonElement* button);

	void On(const lev::Event& event) override;
};