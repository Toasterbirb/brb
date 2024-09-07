#pragma once

#include "string.hpp"
#include "types.hpp"

namespace brb
{
	void print(const char* str);
	void print(const char* str, const u64 len);

	template <u64 str_size>
	void print(string<str_size>& str)
	{
		if (str.empty())
			return;

		print(str.data(), str.size());
	}
}
