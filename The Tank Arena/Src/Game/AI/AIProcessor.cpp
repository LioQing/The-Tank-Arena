#include "AIProcessor.hpp"

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
		*control.turret_dir.load() = (*data.player_pos - *data.ai_pos.at(control.GetEntityID())).Normalize();
	}
}
