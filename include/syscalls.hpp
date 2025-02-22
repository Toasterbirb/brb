#pragma once

#include "types.hpp"

namespace brb
{
	constexpr static u32 stdin = 0;
	constexpr static u32 stdout = 1;

	namespace syscall
	{
		extern "C" u64 read(const u32 fd, const void* buffer, const u64 size);
		extern "C" void write(const u32 fd, const char* str, const u64 len);
		extern "C" void exit(const u8 exit_code);
		extern "C" u64 open(const char* const filename, const i32 flags, const i32 mode);
		extern "C" void* mmap(const u64 address, const u64 len, const u64 prot, const u64 flags, const u64 fd, const u64 off);
		extern "C" void kill(const i64 pid, const i32 sig);
		extern "C" u64 execve(const char* filename, const char* const argv[], const char* const envp[]);
		extern "C" u64 fork();
		extern "C" void wait4(const u64 pid, const i32* const stat_addr, const i32 options);
		extern "C" void getcwd(char* const buffer, const u64 size);
		extern "C" void chdir(const char* path);
		extern "C" void setuid(const u64 uid);
		extern "C" u64 getuid();
	}
}
