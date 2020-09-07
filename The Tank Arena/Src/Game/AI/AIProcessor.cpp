#include "AIProcessor.hpp"

#include <algorithm>

namespace ai
{
	std::function<void(AIControlComponent&, const AIProcessData&)> IDToProcess(int id)
	{
		switch (id)
		{
			case 1: return Normal; break;
		}
	}

	void Normal(AIControlComponent& control, const AIProcessData& data)
	{
		// movement
		*control.movement.load() = lio::Vec2f::Left();

		// turret rotation
		auto position = data.ai_pos.at(control.GetEntityID());
		auto displacement_line = lio::LineSegf(position, data.player_pos);

		if (std::find_if(data.level.edge_pool.begin(), data.level.edge_pool.end(), [&](const auto& edge) -> bool {
				auto edgef = edge.edge * data.level.tile_size * data.scale.Get();
				return edgef.Intersect(displacement_line);
			}) == data.level.edge_pool.end())
		{
			*control.turret_dir.load() = (data.player_pos - position).Normalize();
		}
	}
}
