#pragma once

#include "string.hpp"
#include "syscalls.hpp"
#include "types.hpp"

namespace brb
{
	template <u64 str_size>
	void read(string<str_size>& str)
	{
		u64 bytes_read = syscall::read(str.data(), str.capacity());
		str.set_size(bytes_read);
	}
}
