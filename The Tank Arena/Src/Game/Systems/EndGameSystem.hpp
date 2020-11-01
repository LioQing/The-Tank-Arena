#pragma once

#include "System.hpp"

struct EndGameSystem : System
{
	EndGameSystem(lic::Entity& arena_entity);

	void Update() override;

private:

	lic::Entity& arena_entity;
};