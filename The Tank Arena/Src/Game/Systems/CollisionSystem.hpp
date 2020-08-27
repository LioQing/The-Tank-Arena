#pragma once

#include <lic.hpp>

#include "System.hpp"

struct CollisionSystem : System
{
	CollisionSystem(const lic::Entity& arena_entity);

	void Update() override;
	void Draw();

private:

	const lic::Entity& m_arena_entity;
};