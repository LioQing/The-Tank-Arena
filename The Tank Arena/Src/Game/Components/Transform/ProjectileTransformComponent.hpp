#pragma once

#include <LioGraphics.hpp>
#include <lic.hpp>

struct ProjectileTransformComponent : lic::Component
{
	float speed;
	float radius;

	lio::Vec2f position = lio::Vec2f::Zero();
	lio::Vec2f velocity = lio::Vec2f::Zero();

	ProjectileTransformComponent(float speed, float radius);
};