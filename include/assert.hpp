#pragma once

#include "process.hpp"
#include "syscalls.hpp"

namespace brb
{
	class string;

	void assert(const bool condition, string& msg);
	void assert(const bool condition, const char* msg);

	constexpr void assert(const bool condition)
	{
		if (condition)
			return;

		abort();
	}
}
