#pragma once

#include <lic.hpp>
#include <LioGraphics.hpp>
#include <SFML/Graphics.hpp>

struct TankTransformComponent : lic::Component
{
	const float speed;
	const float turret_a_speed;
	const int width;

	lio::Vec2f position = lio::Vec2f::Zero();
	lio::Vec2f velocity = lio::Vec2f::Zero();

	float hull_rotation = 0.f;
	float turret_rotation = 0.f;

	TankTransformComponent(int width, float speed = 1.f, float turret_a_speed = 1.f);
};