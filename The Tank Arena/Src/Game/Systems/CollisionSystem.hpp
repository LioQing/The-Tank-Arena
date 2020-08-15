#pragma once

#include "System.hpp"

struct CollisionSystem : System
{
	void Update() override;
	void Draw();
};