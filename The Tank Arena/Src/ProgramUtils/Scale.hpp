#pragma once

#include <SFML/Graphics.hpp>
#include <LioGraphics.hpp>

class Scale
{
private:

	float m_scale = 1.f;

public:

	Scale() = default;
	Scale(float scale);

	float Get() const;
	void Set(float scale);

	lio::Vec2f Vec2f() const;
	sf::Vector2f sfVec2f() const;

	Scale operator*(float factor) const;
};