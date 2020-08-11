#pragma once

#include <lic.hpp>
#include <LioGraphics.hpp>
#include <SFML/Graphics.hpp>

struct TankTransformComponent : public lic::Component
{
	const float max_speed;
	const float max_hull_a_speed;
	const float max_turret_a_speed;

	lio::Vec2f position = lio::Vec2f::Zero();
	float hull_rotation = 0.f;
	float turret_rotation = 0.f;

	float speed = 0.f;
	float hull_a_speed = 0.f;
	float turret_a_speed = 0.f;

	TankTransformComponent(float max_speed = 1.f, float max_hull_a_speed = 1.f, float max_turret_a_speed = 1.f);
};