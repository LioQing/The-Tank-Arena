#include "MinorUtils.hpp"

namespace lio
{
	float rotbound(float rad)
	{
		if (rad > M_PI)
			while (rad > M_PI) rad -= M_PI * 2;
		else
			while (rad < -M_PI) rad += M_PI * 2;
		return rad;
	}

	bool inview(const sf::FloatRect& rect, const sf::View& view)
	{
		auto view_bound = sf::FloatRect{
			view.getCenter().x - view.getSize().x / 2.f,
			view.getCenter().y - view.getSize().y / 2.f,
			view.getSize().x,
			view.getSize().y
		};

		if (rect.left > view_bound.left + view_bound.width ||
			rect.top > view_bound.top + view_bound.height ||
			rect.left + rect.width < view_bound.left ||
			rect.top + rect.height < view_bound.top)
			return false;

		return true;
	}

	bool inview(const sf::FloatRect& rect, const sf::FloatRect& view_bound)
	{
		if (rect.left > view_bound.left + view_bound.width ||
			rect.top > view_bound.top + view_bound.height ||
			rect.left + rect.width < view_bound.left ||
			rect.top + rect.height < view_bound.top)
			return false;

		return true;
	}
}