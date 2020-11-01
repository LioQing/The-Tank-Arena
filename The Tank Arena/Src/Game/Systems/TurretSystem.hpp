#pragma once

#include "System.hpp"

struct TurretSystem : System
{
	TurretSystem(lic::Entity& arena_entity);

	void Update() override;

private:

	lic::Entity& arena_entity;
};