#pragma once

#include "types.hpp"

namespace brb
{
	template <typename T>
	T square(T x)
	{
		return x * x;
	}

	template <typename T>
	mf64 pow(T x, i64 power)
	{
		// a very naive implementation
		// pls optimize with some assembly magic

		mf64 result{1};

		if (power >= 0)
		{
			for (mu64 i = 0; i < power; ++i)
				result *= x;
		}
		else
		{
			f64 reverse_divisor = 1.0 / x;
			for (mi64 i = 0; i > power; --i)
				result *= reverse_divisor;
		}

		return result;
	}

	template <typename T>
	constexpr T floor(T x)
	{
		return static_cast<i64>(x);
	}
}
