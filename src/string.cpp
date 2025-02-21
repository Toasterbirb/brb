#include "string.hpp"

namespace brb
{
	string::string(const char* const str)
	{
		const u64 size = strlen(str);
		_data.resize(size);

		for (u64 i = 0; i < size; ++i)
			_data[i] = str[i];
	}

	string::string(const char c, const u64 size)
	{
		_data.resize(size);

		fill<char>(_data.data(), size, c);
	}

	string::string(string& str)
	{
		_data.resize(str.size());
		memcpy(str.data(), _data.data(), _data.size());
	}

	string::string(const string& str)
	{
		_data.resize(str.size());
		for (u64 i = 0; i < str.size(); ++i)
			_data[i] = str[i];
	}

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
