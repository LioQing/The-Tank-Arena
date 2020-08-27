#pragma once

#include <lic.hpp>

#include "System.hpp"

struct CrosshairSystem : System
{
	CrosshairSystem(lic::Entity& arena_entity);

	void Update() override;

private:

	lic::Entity& arena_entity;
};