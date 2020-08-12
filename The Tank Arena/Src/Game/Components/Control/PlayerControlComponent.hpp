#pragma once

#include <lic.hpp>
#include <array>

struct PlayerControlComponent : lic::Component
{
	enum Keys : size_t
	{
		UP = 0u,
		DOWN,
		LEFT,
		RIGHT,

		SIZE
	};

	std::array<bool, Keys::SIZE> key_pressed;

	PlayerControlComponent();
};