#pragma once

#include "types.hpp"

namespace brb
{
	template <typename T>
	constexpr T square(const T x)
	{
		return x * x;
	}

	static_assert(square(2) == 4);
	static_assert(square(23) == 529);
	static_assert(square(-124) == 15376);
	static_assert(square(-42) == 1764);

	template <typename T>
	constexpr f64 pow(const T x, const i64 power)
	{
		// a very naive implementation
		// pls optimize with some assembly magic

		f64 result{1};

		if (power >= 0)
		{
			for (i64 i = 0; i < power; ++i)
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

	static_assert(pow(2, 2) == 4);
	static_assert(pow(3, 9) == 19683);
	static_assert(pow(5, -3) >= 0.008 && pow(5, -3) < 0.009);

	template <typename T>
	constexpr T floor(const T x)
	{
		return static_cast<i64>(x);
	}

	static_assert(floor(0.4124) == 0);
	static_assert(floor(4.52345) == 4);
	static_assert(floor(-32.6581) == -32);
	static_assert(floor(-9467.783) == -9467);

	template <typename T>
	constexpr T abs(const T x)
	{
		const T bitmask = x >> (sizeof(T) * 8 - 1);
		return ((bitmask + x) ^ bitmask);
	}

	static_assert(abs(-34234) == 34234);
	static_assert(abs(34234) == 34234);
	static_assert(abs(0) == 0);
}
