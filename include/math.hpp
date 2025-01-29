#pragma once

#include "types.hpp"

namespace brb
{
	template <typename T>
	T square(const T x)
	{
		return x * x;
	}

	template <typename T>
	f64 pow(const T x, const i64 power)
	{
		// a very naive implementation
		// pls optimize with some assembly magic

		f64 result{1};

		if (power >= 0)
		{
			for (u64 i = 0; i < power; ++i)
				result *= x;
		}
		else
		{
			const f64 reverse_divisor = 1.0 / x;
			for (i64 i = 0; i > power; --i)
				result *= reverse_divisor;
		}

		return result;
	}

	template <typename T>
	constexpr T floor(const T x)
	{
		return static_cast<i64>(x);
	}
}
