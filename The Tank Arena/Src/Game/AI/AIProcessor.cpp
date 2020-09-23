#include "AIProcessor.hpp"

#include <cmath>
#include <algorithm>

namespace ai
{
	std::function<void(AIHandle&, const AIProcessData&)> IDToProcess(int id)
	{
		switch (id)
		{
			case 1: return Normal; break;
		}
	}

	void Normal(AIHandle& handle, const AIProcessData& data)
	{
		if (data.ai_data.at(handle.id).is_dead)
			return;

		auto GenAction = [&]() -> void
		{
			handle.current_state = static_cast<AIHandle::State>(lio::randomu(0u, AIHandle::State::SIZE));

			if (handle.current_state == AIHandle::State::IDLE)
			{
				handle.idle_length = lio::randomu(500, 1000);
				handle.idle_timer = 0.f;
			}

			if (handle.current_state == AIHandle::State::WANDERING)
				handle.current_node = handle.current_node->GetChild();
			else
				*handle.control.movement.load() = lio::Vec2f::Zero();
		};

		// movement
		if (handle.current_state == AIHandle::State::WANDERING)
		{
			// pathfind
			if (!handle.current_node || handle.current_node == handle.pathfinder->GetEndNode())
			{
				// start pos
				lio::Vec2i start_pos = data.ai_data.at(handle.id).position / data.scale.Get() / data.level.tile_size;
				if (handle.current_node && handle.current_node == handle.pathfinder->GetEndNode())
					start_pos = handle.current_node->GetPos();

				// end pos
				constexpr auto scan_size = 4; // config
				std::vector<lio::Vec2i> empty_pos;
				for (auto y = 0u; y < scan_size; ++y)
				{
					for (auto x = 0u; x < scan_size; ++x)
					{
						auto pos = start_pos - lio::Vec2i(scan_size / 2 - x, scan_size / 2 - y);
						if (pos.x < data.level.size.x &&
							pos.y < data.level.size.y &&
							pos.x >= 0 &&
							pos.y >= 0 &&
							data.level.level.At(pos.x, pos.y).id == 0)
						{
							empty_pos.emplace_back(pos.x, pos.y);

						}
					}
				}
				auto end_pos = empty_pos.at(lio::randomu(0u, empty_pos.size()));

				// find path
				handle.pathfinder = std::make_shared<lio::AStarPathfinder<uint32_t, Cell>>(
					data.level.level.matrix,
					data.level.size,
					start_pos,
					end_pos
					);

				handle.current_node = handle.pathfinder->GetStartNode();
			}

			// go to node
			if (handle.current_node)
				*handle.control.movement.load() =
				(((handle.current_node->GetPos() + lio::Vec2f(.5f, .5f))
					* data.level.tile_size * data.scale.Get()
					- data.ai_data.at(handle.id).position)
					* lio::Vec2i(1, -1)).Normalized();

			// arrived node
			if (((handle.current_node->GetPos() + lio::Vec2f(.5f, .5f)) * data.level.tile_size * data.scale.Get())
				.Distance(data.ai_data.at(handle.id).position)
				< .2 * data.level.tile_size * data.scale.Get())
			{
				if (handle.current_node == handle.pathfinder->GetStartNode())
					GenAction();
				else
					handle.current_node = handle.current_node->GetChild();
			}
		}
		// idle
		else if (handle.current_state == AIHandle::State::IDLE)
		{
			handle.idle_timer += data.dt;

			if (handle.idle_timer >= handle.idle_length)
				GenAction();
		}

		// turret rotation
		auto position = data.ai_data.at(handle.id).position;
		auto displacement_line = lio::LineSegf(position, data.player_pos);

		if (std::find_if(data.level.edge_pool.begin(), data.level.edge_pool.end(), [&](const auto& edge) -> bool {
				auto edgef = edge.edge * data.level.tile_size * data.scale.Get();
				return edgef.Intersect(displacement_line);
			}) == data.level.edge_pool.end())
		{
			auto target_dir = (data.player_pos - position).Normalize();
			*handle.control.turret_dir.load() = target_dir;
			handle.control.turret_lock.store(false);

			// fire
			if (std::abs(std::atan2(target_dir.y, target_dir.x) - data.ai_data.at(handle.id).turret_rotation) - M_PI / 2 < .1f)
				handle.control.fire.store(true);
			else
				handle.control.fire.store(false);
		}
		else
		{
			handle.control.turret_lock.store(true);
			handle.control.fire.store(false);
		}
	}
}
