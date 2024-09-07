#include "syscalls.hpp"

namespace brb
{
	namespace syscall
	{
		mu64 read(const void* buffer, u64 size)
		{
			mu64 bytes_read{0};

			asm volatile (R"(
				.global read
					read:
						mov $0, %%rax
						mov $0, %%rdi
						mov %[buffer], %%rsi
						mov %[size], %%rdx
						syscall

						mov %%rax, %[bytes_read]
				)"
				:
				: [buffer] "m" (buffer), [size] "m" (size), [bytes_read] "m" (bytes_read)
				: "rax", "rdi", "rsi", "rdx"
			);

			return bytes_read;
		}

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
