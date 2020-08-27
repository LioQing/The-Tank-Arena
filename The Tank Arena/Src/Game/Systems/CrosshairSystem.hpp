#pragma once

#include <lic.hpp>

#include "System.hpp"

struct CrosshairSystem : System
{
	CrosshairSystem(const lic::Entity& arena_entity);

	void Update() override;

private:

	const lic::Entity& arena_entity;
};