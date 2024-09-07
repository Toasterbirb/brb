#pragma once

#include "process.hpp"
#include "types.hpp"

namespace brb
{
	template <u64 str_len>
	class string;

	template <u64 str_len>
	void ensure(const bool condition, string<str_len>& msg);
	void ensure(const bool condition, const char* msg);

	constexpr void ensure(const bool condition)
	{
		if (condition)
			return;

		exit(-2);
	}
}
