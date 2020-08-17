#include "InputSystem.hpp"

#include <SFML/System.hpp>
#include <lic.hpp>

#include "../Components.hpp"
#include "../../ProgramUtils.hpp"

void InputSystem::Update()
{
	for (auto& control : manager->Filter<PlayerControlComponent>().Component())
	{
		// movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			control.movement.x = -1.f;
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			control.movement.x = 1.f;
		else
			control.movement.x = 0.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			control.movement.y = 1.f;
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			control.movement.y = -1.f;
		else
			control.movement.y = 0.f;

		control.movement.Normalize();

		// turret direction
		if (manager->HasComponent<TankTransformComponent>(control.GetEntityID()))
		{
			auto& transform = manager->GetComponent<TankTransformComponent>(control.GetEntityID());

			auto dir_vec =
				lio::stolvec<float>(program_info->window->mapPixelToCoords(sf::Mouse::getPosition(*program_info->window))) -
				transform.position;
			dir_vec.Normalize();

			control.turret_dir = dir_vec;
		}
	}
}
