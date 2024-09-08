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
	T pow(T x, u64 power)
	{
		// a very naive implementation
		// pls optimize with some assembly magic

		T result{1};
		for (mu64 i = 0; i < power; ++i)
			result *= x;

		return result;
	}

	template <typename T>
	constexpr T floor(T x)
	{
		return static_cast<i64>(x);
	}
}
