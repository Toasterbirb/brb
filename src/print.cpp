#include "print.hpp"
#include "string.hpp"
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

	void print(string& str)
	{
		if (str.empty())
			return;

		print(str.data(), str.size());
	}
}
