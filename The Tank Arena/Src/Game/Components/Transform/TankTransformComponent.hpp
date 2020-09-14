#pragma once

#include <lic.hpp>
#include <LioGraphics.hpp>
#include <SFML/Graphics.hpp>

struct TankTransformComponent : lic::Component
{
	const float speed;
	const lio::Vec2i size;

	lio::Vec2f position = lio::Vec2f::Zero();
	lio::Vec2f velocity = lio::Vec2f::Zero();
	lio::Vec2f scaled_velocity = lio::Vec2f::Zero();
	bool reverse = false;

	float angular_velocity = 0.f;
	float hull_rotation = 0.f;
	float turret_rotation = 0.f;

	TankTransformComponent(const lio::Vec2i& size, float speed = 1.f);
};