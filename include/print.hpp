#pragma once

#include "types.hpp"

namespace brb
{
	class string;

	void print(const char* str);
	void print(const char* str, const u64 len);
	void print(string& str);
}
