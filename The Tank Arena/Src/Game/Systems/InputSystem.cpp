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
		// keyboard
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

		// joystick
		if (sf::Joystick::isConnected(0))
		{
			auto move_axis = lio::Vec2f(
				sf::Joystick::getAxisPosition(0, sf::Joystick::X),
				sf::Joystick::getAxisPosition(0, sf::Joystick::Y));

			if (move_axis.Magnitude() > 15.f)
				control.movement = (move_axis.Cast<double>() - 15.f) / 85.f * lio::Vec2(1, -1);
		}

		if (control.movement.Magnitude() > 1.f)
			control.movement.Normalize();

		// turret direction
		if (manager->HasComponent<TankTransformComponent>(control.GetEntityID()))
		{
			auto& transform = manager->GetComponent<TankTransformComponent>(control.GetEntityID());

			// mouse
			static auto pre_mouse_pos = lio::Vec2f::Zero();

			if (!control.is_joystick || pre_mouse_pos != lio::stolvec<float>(sf::Mouse::getPosition()))
			{
				auto dir_vec =
					lio::stolvec<float>(program_info->window->mapPixelToCoords(sf::Mouse::getPosition(*program_info->window))) -
					transform.position;
				control.turret_dir = dir_vec;

				control.is_joystick = false;
			}
			pre_mouse_pos = lio::stolvec<float>(sf::Mouse::getPosition());

			// joystick
			if (sf::Joystick::isConnected(0))
			{
				auto turret_axis = lio::Vec2f(
					sf::Joystick::getAxisPosition(0, sf::Joystick::U),
					sf::Joystick::getAxisPosition(0, sf::Joystick::V));

				if (turret_axis.Magnitude() > 15.f)
				{
					control.turret_dir = turret_axis;
					control.is_joystick = true;
				}
			}

			control.turret_dir.Normalize();
		}

		// fire
		if (manager->HasComponent<TurretComponent>(control.GetEntityID()))
		{
			auto& turret = control.GetEntity().GetComponent<TurretComponent>();

			if (turret.interval_timer >= turret.interval && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				turret.interval_timer -= turret.interval;
				control.fire = true;
			}
			else if (turret.interval_timer < turret.interval)
			{
				turret.interval_timer += dt;
				control.fire = false;
			}
		}
		else
		{
			control.fire = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		}
	}
}
