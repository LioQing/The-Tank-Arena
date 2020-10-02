#pragma once

#include <vector>

#include "../Elements/ButtonElements/ButtonElement.hpp"

class InputManager
{
private:

	std::vector<std::string> buttons;

public:

	void AddButton(const std::string& button_id);
};