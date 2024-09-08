#pragma once

#include "types.hpp"

namespace brb
{
	namespace syscall
	{
		mu64 read(const void* buffer, u64 size);
		void write(const char* str, u64 len);
		void exit(const u8 exit_code);
		void* mmap(u64 address, u64 len, u64 prot, u64 flags, u64 fd, u64 off);
		void kill(i64 pid, i32 sig);
	}
}
