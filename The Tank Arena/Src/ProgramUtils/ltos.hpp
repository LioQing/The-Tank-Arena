#pragma once

#include <type_traits>
#include <SFML/Graphics.hpp>
#include <LioGraphics.hpp>

namespace ltos
{
	template <typename T>
	concept IsArithmetic = std::is_arithmetic<T>::value;

	template <IsArithmetic T, IsArithmetic U>
	sf::Vector2<T> ToSFVec(const lio::Vec2<U>& vec)
	{
		return sf::Vector2<T>(vec.x, vec.y);
	}
}