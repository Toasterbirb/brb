#pragma once

#include "string.hpp"
#include "types.hpp"

namespace brb
{
	void print(const char* str);
	void print(const char* str, const u64 len);
	void print(string& str);

	template<typename T>
	void print(const T num)
	{
		string s(num);
		print(s);
	}

	template<typename T>
	void println(const T v)
	{
		print(v);
		print("\n", 1);
	}

	template<typename... Args>
	void printv(const Args&... args)
	{
		(print(args), ...);
	}
}
