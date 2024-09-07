#pragma once

#include "types.hpp"

namespace brb
{
	namespace syscall
	{
		void write(const char* str, u64 len);
		void exit(const u8 exit_code);
	}
}
