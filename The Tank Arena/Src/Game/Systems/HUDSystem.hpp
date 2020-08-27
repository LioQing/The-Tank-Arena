#pragma once

#include <lic.hpp>
#include <lev.hpp>

#include "System.hpp"

struct HUDSystem : System, lev::Listener
{
	HUDSystem(lic::Entity& arena_entity);

	void Update() override;
	void Draw();

	void On(const lev::Event& event) override;

private:

	lic::Entity& arena_entity;
};