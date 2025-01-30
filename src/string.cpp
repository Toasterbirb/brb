#include "string.hpp"

namespace brb
{
	u64 string::find(const char c)
	{
		const u64 str_size = _data.size();

		for (u64 i = 0; i < str_size; ++i)
		{
			if (_data[i] == c)
				return i;
		}

		return npos;
	}
}
