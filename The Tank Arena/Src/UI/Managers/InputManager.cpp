#include "InputManager.hpp"

void InputManager::AddButton(const std::string& button_id)
{
	buttons.push_back(button_id);
}
