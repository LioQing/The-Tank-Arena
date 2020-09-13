#pragma once

#include <lic.hpp>
#include <functional>

#include "../Components.hpp"
#include "AIProcessData.hpp"
#include "AIHandle.hpp"

namespace ai
{
	std::function<void(AIHandle&, const AIProcessData&)> IDToProcess(int id);

	void Normal(AIHandle& control, const AIProcessData& data);
}