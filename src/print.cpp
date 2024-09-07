#include "print.hpp"

namespace brb
{
	void print(const char* str)
	{
		u64 len = strlen(str);

		asm volatile (R"(
		.global print_no_len
			print_no_len:
				mov $1, %%rax
				mov $1, %%rdi
				mov %[str], %%rsi
				mov %[len], %%rdx
				syscall
		)"
		:
		: [str] "m" (str) , [len] "m" (len)
		: "eax", "ebx", "ecx", "edx");
	}

	void print(const char* str, u64 len)
	{
		asm volatile (R"(
		.global print_len
			print_len:
				mov $1, %%rax
				mov $1, %%rdi
				mov %[str], %%rsi
				mov %[len], %%rdx
				syscall
		)"
		:
		: [str] "m" (str) , [len] "m" (len)
		: "eax", "ebx", "ecx", "edx");
	}
}
