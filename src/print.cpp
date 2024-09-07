#include "print.hpp"
#include "syscalls.hpp"

namespace brb
{
	void print(const char* str)
	{
		u64 len = strlen(str);
		syscall::write(str, len);
	}

	void print(const char* str, u64 len)
	{
		syscall::write(str, len);
	}
}
