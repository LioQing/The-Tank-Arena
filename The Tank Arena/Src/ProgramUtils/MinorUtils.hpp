#pragma once

#include <type_traits>
#include <SFML/Graphics.hpp>
#include <LioGraphics.hpp>

namespace lio
{
	template <typename T>
	concept IsArithmetic = std::is_arithmetic<T>::value;

	template <IsArithmetic T, IsArithmetic U>
	sf::Vector2<T> ltosvec(const lio::Vec2<U>& vec)
	{
		return sf::Vector2<T>(vec.x, vec.y);
	}

	float rotbound(float rad);
}