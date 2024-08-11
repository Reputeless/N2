#pragma once
#include <concepts> // std::floating_point
#include "Common.hpp"

namespace seccamp
{
	template <std::floating_point T>
	struct Vector2
	{
		using value_type = T;

		value_type x;

		value_type y;



	};
}
