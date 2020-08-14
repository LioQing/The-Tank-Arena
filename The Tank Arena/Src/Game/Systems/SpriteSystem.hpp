#pragma once

#include <lev.hpp>

#include "System.hpp"

struct SpriteSystem : System, lev::Listener
{
	SpriteSystem();

	void Update() override;
	void Draw();

	void On(const lev::Event& event) override;
};