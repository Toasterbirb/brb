#pragma once

#include "types.hpp"

namespace brb
{
	namespace syscall
	{
		mu64 read(const void* buffer, u64 size);
		void write(const char* str, u64 len);
		void exit(const u8 exit_code);
	}
}
