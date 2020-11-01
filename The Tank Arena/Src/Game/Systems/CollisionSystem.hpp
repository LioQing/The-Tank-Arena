#pragma once

#include <lic.hpp>

#include "System.hpp"

struct CollisionSystem : System
{
	CollisionSystem(lic::Entity& arena_entity);

	void Update() override;
	void Draw();

private:

	lic::Entity& arena_entity;
};