#pragma once

#include "types.hpp"

namespace brb
{
	namespace syscall
	{
		u64 read(const void* buffer, const u64 size);
		void write(const char* str, const u64 len);
		void exit(const u8 exit_code);
		void* mmap(const u64 address, const u64 len, const u64 prot, const u64 flags, const u64 fd, const u64 off);
		void kill(const i64 pid, const i32 sig);
		u64 execve(const char* filename, const char* const argv[], const char* const envp[]);
	}
}
