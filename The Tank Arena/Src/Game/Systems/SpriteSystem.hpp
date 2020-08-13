#pragma once

#include "System.hpp"

struct SpriteSystem : System
{
	void Update() override;
	void Draw();

	void UpdateSpriteScale();
};