#pragma once

#include <memory>
#include <lic.hpp>
#include <AStarPathfinder.hpp>

#include "../Components.hpp"

struct AIHandle
{
	enum State : uint16_t
	{
		IDLE,
		WANDERING,

		SIZE
	};

	lic::EntityID id;
	AIControlComponent& control;
	State current_state = State::WANDERING;

	// idleing
	float idle_length;
	float idle_timer;

	// pathfinding
	std::shared_ptr<lio::AStarPathfinder<uint32_t, Cell>> pathfinder;
	const lio::AStarPathfinder<uint32_t, Cell>::Node* current_node = nullptr;

	AIHandle(lic::EntityID id, AIControlComponent& control);
};
