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
}