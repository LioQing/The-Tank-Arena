#pragma once

#include <SFML/Graphics.hpp>

class Scale
{
private:

	float m_scale = 1.f;

public:

	Scale() = default;
	Scale(float scale);

	sf::Vector2f sfVec2f() const;
};