#include "InputSystem.hpp"

#include <SFML/System.hpp>
#include <lic.hpp>

#include "../Components.hpp"

void InputSystem::Update()
{
	for (auto& control : manager->Filter<PlayerControlComponent>().Component())
	{
		control.key_pressed.at(PlayerControlComponent::Keys::UP) = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		control.key_pressed.at(PlayerControlComponent::Keys::DOWN) = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		control.key_pressed.at(PlayerControlComponent::Keys::LEFT) = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		control.key_pressed.at(PlayerControlComponent::Keys::RIGHT) = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	}
}
