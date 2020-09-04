#pragma once

#include <lic.hpp>
#include <functional>

#include "../Components.hpp"
#include "AIProcessData.hpp"

namespace ai
{
	std::function<void(AIControlComponent&, const AIProcessData&)> IDToProcess(int id);

	void Normal(AIControlComponent& control, const AIProcessData& data);
}