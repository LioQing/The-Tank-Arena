#include "MovementSystem.hpp"

#include "../Components.hpp"
#include "../../ProgramUtils.hpp"

void MovementSystem::Update()
{
	for (auto [control, transform] : manager->Filter<PlayerControlComponent, TankTransformComponent>().Each())
	{
		if (control.movement == lio::Vec2f::Zero())
			continue;

		// rotation
		auto target_rot = M_PI / 2 - atan2(control.movement.y, control.movement.x);
		float diffs[2] = {
			lio::rotbound(target_rot - transform.hull_rotation),
			lio::rotbound(target_rot - lio::rotbound(transform.hull_rotation + M_PI)) };
		auto reverse = std::abs(diffs[1]) < std::abs(diffs[0]) ? true : false;
		auto diff = !reverse ? diffs[0] : diffs[1];
		auto rot_vel = (transform.speed / (transform.size.x * program_info->scale->Get())) * diff / std::abs(diff);

		if (std::abs(diff) > std::abs(rot_vel * space_time_scale))
		{
			transform.hull_rotation += rot_vel * space_time_scale;

			// movement
			auto math_rot = M_PI / 2 - transform.hull_rotation;
			transform.velocity = lio::Vec2f(std::cos(math_rot), -std::sin(math_rot)).Normalized() * (reverse ? -1 : 1);
			transform.position += .5f * transform.speed * transform.velocity * space_time_scale;
		}
		else
		{
			transform.hull_rotation = lio::rotbound(target_rot + reverse * M_PI);

			// movement
			transform.velocity.x = control.movement.x;
			transform.velocity.y = -control.movement.y;
			transform.position += transform.velocity * transform.speed * space_time_scale;
		}
	}
}
