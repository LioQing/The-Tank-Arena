#include "Scale.hpp"

Scale::Scale(float scale)
{
	Set(scale);
}

float Scale::Get() const
{
	return m_scale;
}

void Scale::Set(float scale)
{
	m_scale = scale;
}

lio::Vec2f Scale::Vec2f() const
{
	return lio::Vec2f(m_scale, m_scale);
}

sf::Vector2f Scale::sfVec2f() const
{
	return sf::Vector2f(m_scale, m_scale);
}

Scale Scale::operator*(float factor) const
{
	return Scale(m_scale * factor);
}
