#include "Scale.hpp"

Scale::Scale(float scale)
{
	m_scale = scale;
}

sf::Vector2f Scale::sfVec2f() const
{
	return sf::Vector2f(m_scale, m_scale);
}
