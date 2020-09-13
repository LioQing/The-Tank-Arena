#include "AIProcessor.hpp"

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
		// movement
		if (!handle.current_node)
		{
			auto start_pos = data.ai_pos.at(handle.id) / data.scale.Get() / data.level.tile_size;

			handle.pathfinder = std::make_shared<lio::AStarPathfinder<uint32_t, Cell>>(
				data.level.level.matrix,
				data.level.size,
				start_pos,
				start_pos
				);

			handle.current_node = handle.pathfinder->GetStartNode();
		}
		else
		{
			
		}

		// turret rotation
		auto position = data.ai_pos.at(handle.id);
		auto displacement_line = lio::LineSegf(position, data.player_pos);

		if (std::find_if(data.level.edge_pool.begin(), data.level.edge_pool.end(), [&](const auto& edge) -> bool {
				auto edgef = edge.edge * data.level.tile_size * data.scale.Get();
				return edgef.Intersect(displacement_line);
			}) == data.level.edge_pool.end())
		{
			*handle.control.turret_dir.load() = (data.player_pos - position).Normalize();
		}
	}
}
