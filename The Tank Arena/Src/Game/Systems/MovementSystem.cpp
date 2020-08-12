#include "MovementSystem.hpp"

#include "../Components.hpp"

void MovementSystem::Update()
{
	for (auto [control, transform] : manager->Filter<PlayerControlComponent, TankTransformComponent>().Each())
	{
		// rotation
		if (control.key_pressed.at(control.LEFT) && !control.key_pressed.at(control.RIGHT))
			transform.hull_a_velocity = -1.f;
		else if (!control.key_pressed.at(control.LEFT) && control.key_pressed.at(control.RIGHT))
			transform.hull_a_velocity = 1.f;
		else
			transform.hull_a_velocity = 0.f;

		// movement
		if (control.key_pressed.at(control.UP) && !control.key_pressed.at(control.DOWN))
			transform.velocity = lio::Vec2f::Down().Rotated(transform.hull_rotation).Normalized();
		else if (!control.key_pressed.at(control.UP) && control.key_pressed.at(control.DOWN))
			transform.velocity = lio::Vec2f::Up().Rotated(transform.hull_rotation).Normalized();
		else
			transform.velocity = lio::Vec2f::Zero();

		transform.hull_rotation += transform.hull_a_velocity * transform.hull_a_speed * 
			(1.f - .5f * static_cast<float>(transform.velocity.Magnitude()));
		transform.turret_rotation += transform.hull_a_velocity * transform.hull_a_speed * 
			(1.f - .5f * static_cast<float>(transform.velocity.Magnitude()));

		transform.position += transform.velocity * transform.speed * (1.f - .25f * abs(transform.hull_a_velocity));
	}
}
