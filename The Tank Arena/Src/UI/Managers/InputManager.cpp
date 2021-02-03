#include "InputManager.hpp"

#include "../Events.hpp"

InputManager::InputManager()
{
	Listen<InputEvent>();
}

void InputManager::AddButton(ButtonElement* button)
{
	buttons.push_back(button);
}

void InputManager::On(const lev::Event& event)
{
	if (event.Is<InputEvent>())
	{
		const auto& input = static_cast<const InputEvent&>(event);

		for (const auto& button : buttons)
		{
			if (!button->is_active) continue;

			if (input.mouse_pos.x < button->GetTrigger().GetPosition().x ||
				input.mouse_pos.y < button->GetTrigger().GetPosition().y ||
				input.mouse_pos.x > button->GetTrigger().GetPosition().x + button->GetTrigger().GetSize().x ||
				input.mouse_pos.y > button->GetTrigger().GetPosition().y + button->GetTrigger().GetSize().y) // not in trigger box
			{
				if (input.is_hover)
				{
					button->is_hovering = false;
				}
				else if (input.is_release)
				{
					button->is_hovering = false;
					button->is_down = false;
				}
			}
			else if (input.is_hover)
			{
				button->is_hovering = true;
				button->OnHover();
			}
			else if (input.is_release)
			{
				button->is_hovering = true;
				if (button->is_down)
				{
					button->is_down = false;
					button->OnRelease();
				}
			}
			else if (input.is_click && input.button == sf::Mouse::Left)
			{
				button->is_down = true;
				button->OnClick();
			}
		}
	}
}
