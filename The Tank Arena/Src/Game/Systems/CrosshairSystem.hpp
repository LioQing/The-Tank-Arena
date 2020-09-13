#pragma once

#include <lic.hpp>
#include <SFML/Graphics.hpp>

#include "System.hpp"

struct CrosshairSystem : System
{
	CrosshairSystem(lic::Entity& arena_entity, const sf::View& ui_view);

	void Update() override;

private:

	lic::Entity& arena_entity;
	const sf::View& ui_view;
};