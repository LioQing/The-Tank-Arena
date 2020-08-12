#include "MovementSystem.hpp"

#include "../Components.hpp"
#include "../../ProgramUtils.hpp"

void MovementSystem::Update()
{
	for (auto [control, transform] : manager->Filter<PlayerControlComponent, TankTransformComponent>().Each())
	{
		// target vel
		lio::Vec2f target_vel = lio::Vec2f::Zero();

		std::string str = "";

		if (control.key_pressed.at(control.LEFT) && !control.key_pressed.at(control.RIGHT))
		{
			target_vel.x = -1.f; 
			str += "Left  ";
		}
		else if (!control.key_pressed.at(control.LEFT) && control.key_pressed.at(control.RIGHT))
		{
			target_vel.x = 1.f; 
			str += "Right ";
		}

		if (control.key_pressed.at(control.UP) && !control.key_pressed.at(control.DOWN))
		{
			target_vel.y = 1.f; 
			str += "Up";
		}
		else if (!control.key_pressed.at(control.UP) && control.key_pressed.at(control.DOWN))
		{
			target_vel.y = -1.f; 
			str += "Down";
		}

		std::cout << str << std::endl;

		target_vel.Normalize();

		// rotation
		if (target_vel != lio::Vec2f::Zero())
		{
			auto target_rot = M_PI / 2 - atan2(target_vel.y, target_vel.x);
			float diffs[2] = {
				lio::rotbound(target_rot - transform.hull_rotation),
				lio::rotbound(target_rot - lio::rotbound(transform.hull_rotation + M_PI)) };
			auto reverse = std::abs(diffs[1]) < std::abs(diffs[0]) ? true : false;
			auto diff = !reverse ? diffs[0] : diffs[1];
			auto rot_vel = (transform.speed / (transform.width * program_info->scale->Get())) * diff / std::abs(diff);

			if (std::abs(diff) > std::abs(rot_vel * space_time_scale))
			{
				transform.hull_rotation += rot_vel * space_time_scale;
				transform.turret_rotation += rot_vel * space_time_scale;

				// movement
				auto math_rot = M_PI / 2 - transform.hull_rotation;
				transform.velocity = lio::Vec2f(std::cos(math_rot), -std::sin(math_rot));
				transform.position += .5f * transform.speed * transform.velocity * (reverse ? -1 : 1) * space_time_scale;
			}
			else
			{
				transform.hull_rotation = lio::rotbound(target_rot + reverse * M_PI);
				transform.turret_rotation = lio::rotbound(target_rot + reverse * M_PI);

				// movement
				transform.velocity.x = target_vel.x;
				transform.velocity.y = -target_vel.y;
				transform.position += transform.velocity * transform.speed * space_time_scale;
			}
		}
	}
}
