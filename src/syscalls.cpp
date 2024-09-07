#include "syscalls.hpp"

namespace brb
{
	namespace syscall
	{
		void write(const char* str, u64 len)
		{
			asm volatile (R"(
				.global write
					write:
						mov $1, %%rax
						mov $1, %%rdi
						mov %[str], %%rsi
						mov %[len], %%rdx
						syscall
				)"
				:
				: [str] "m" (str) , [len] "m" (len)
				: "eax", "ebx", "ecx", "edx"
			);
		}

		void exit(const u8 exit_code)
		{
			asm(R"(
				.global exit
					exit:
						mov $1, %eax
						mov %edi, %ebx
						int $0x80
			)");
		}
	}
}
