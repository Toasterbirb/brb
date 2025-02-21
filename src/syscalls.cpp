#include "syscalls.hpp"

namespace brb
{
	namespace syscall
	{
		u64 read(const u32 fd, const void* buffer, const u64 size)
		{
			u64 bytes_read{0};

			asm volatile (R"(
				.global read
					read:
						mov $0, %%rax
						mov %[fd], %%rdi
						mov %[buffer], %%rsi
						mov %[size], %%rdx
						syscall

						mov %%rax, %[bytes_read]
				)"
				:
				: [fd] "m" (fd), [buffer] "m" (buffer), [size] "m" (size), [bytes_read] "m" (bytes_read)
				: "rax", "rdi", "rsi", "rdx"
			);

			return bytes_read;
		}

		void write(const u32 fd, const char* str, const u64 len)
		{
			asm volatile (R"(
				.global write
					write:
						mov $1, %%rax
						mov %[fd], %%rdi
						mov %[str], %%rsi
						mov %[len], %%rdx
						syscall
				)"
				:
				: [fd] "m" (fd), [str] "m" (str) , [len] "m" (len)
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

		u64 open(const char* const filename, const i32 flags, const i32 mode)
		{
			u64 ret_value{0};

			asm volatile (R"(
			.global open
				open:
					mov $2, %%rax
					mov %[filename], %%rdi
					mov %[flags], %%rsi
					mov %[mode], %%rdx
					syscall

					mov %%rax, %[ret_value]
			)"
			:
			: [filename] "m" (filename), [flags] "m" (flags), [mode] "m" (mode), [ret_value] "m" (ret_value)
			: "rax", "rdi", "rsi", "rdx");

			return ret_value;
		}

		void* mmap(const u64 address, const u64 len, const u64 prot, const u64 flags, const u64 fd, const u64 off)
		{
			void* ret_addr{nullptr};

			asm volatile (R"(
				.global mmap
					mmap:
						mov $9, %%rax
						mov %[address], %%rdi
						mov %[len], %%rsi
						mov %[prot], %%rdx
						mov %[flags], %%r10
						mov %[fd], %%r8
						mov %[off], %%r9
						syscall

						mov %%rax, %[ret_addr]
				)"
				:
				: [address] "m" (address), [len] "m" (len), [prot] "m" (prot), [flags] "m" (flags), [fd] "m" (fd), [off] "m" (off), [ret_addr] "m" (ret_addr)
				: "rax", "rdi", "rsi", "rdx", "r10", "r8", "r9"
			);

			return ret_addr;
		}

		void kill(const i64 pid, const i32 sig)
		{
			asm volatile (R"(
				.global kill
					kill:
						mov $62, %%rax
						mov %[pid], %%rdi
						mov %[sig], %%rsi
						syscall
				)"
				:
				: [pid] "m" (pid), [sig] "m" (sig)
				: "rax", "rdi", "rsi"
			);
		}

		u64 execve(const char* filename, const char* const argv[], const char* const envp[])
		{
			u64 exec_ret{0};

			asm volatile (R"(
			.global execve
				execve:
					mov $59, %%rax
					mov %[filename], %%rdi
					mov %[argv], %%rsi
					mov %[envp], %%rdx
					syscall

					mov %%rax, %[exec_ret]
			)"
			:
			: [filename] "m" (filename), [argv] "m" (argv), [envp] "m" (envp), [exec_ret] "m" (exec_ret)
			: "rax", "rdi", "rsi", "rdx");

			return exec_ret;
		}

		u64 fork()
		{
			u64 pid{0};
			asm volatile (R"(
			.global fork
				fork:
					mov $57, %%rax
					syscall

					mov %%rax, %[pid]
			)"
			:
			: [pid] "m" (pid)
			: "rax");

			return pid;
		}

		void wait4(const u64 pid, const i32* const stat_addr, const i32 options)
		{
			asm volatile (R"(
			.global wait4
				wait4:
					mov $61, %%rax
					mov %[pid], %%rdi
					mov %[stat_addr], %%rsi
					mov %[options], %%rdx
					mov $0, %%r10
					syscall
			)"
			:
			: [pid] "m" (pid), [stat_addr] "m" (stat_addr), [options] "m" (options)
			: "rax", "rdi", "rsi", "rdx", "r10");
		}

		void getcwd(char* const buffer, const u64 size)
		{
			asm volatile (R"(
			.global getcwd
				getcwd:
					mov $79, %%rax
					mov %[buffer], %%rdi
					mov %[size], %%rsi
					syscall
			)"
			:
			: [buffer] "m" (buffer), [size] "m" (size)
			: "rax", "rdi", "rsi");
		}

		void chdir(const char* path)
		{
			asm volatile (R"(
			.global chdir
				chdir:
					mov $80, %%rax
					mov %[path], %%rdi
					syscall
			)"
			:
			: [path] "m" (path)
			: "rax", "rdi");
		}

		void setuid(const u64 uid)
		{
			asm volatile (R"(
			.global setuid
				setuid:
					mov $105, %%rax
					mov %[uid], %%rdi
					syscall
			)"
			:
			: [uid] "m" (uid)
			: "rax", "rdi");
		}

		u64 getuid()
		{
			u64 uid{0};

			asm volatile (R"(
			.global getuid
				getuid:
					mov $102, %%rax
					syscall

					mov %%rax, %[uid]
			)"
			:
			: [uid] "m" (uid)
			: "rax", "rdi");

			return uid;
		}
	}
}
