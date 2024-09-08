#pragma once

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

		syscall::kill(0, 6); // abort
	}
}
