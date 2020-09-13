#pragma once

#include <memory>
#include <lic.hpp>
#include <AStarPathfinder.hpp>

#include "../Components.hpp"

struct AIHandle
{
	lic::EntityID id;
	AIControlComponent& control;

	std::shared_ptr<lio::AStarPathfinder<uint32_t, Cell>> pathfinder;
	const lio::AStarPathfinder<uint32_t, Cell>::Node* current_node = nullptr;

	AIHandle(lic::EntityID id, AIControlComponent& control);
};
