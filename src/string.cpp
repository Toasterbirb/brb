#include "string.hpp"
#include "math.hpp"

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

	string::string(const i64 num)
	{
		// this code is copy pasted from some asm implementation I did in the past
		// optimizations are FOR SURE on the table and should be attempted

		// count the digits
		const u8 digit_count = num == 0 ? 1 : [](i64 num) -> u8
		{
			const bool negative_num = num < 0;

			u8 counter{0};
			while (num != 0)
			{
				++counter;
				num /= 10;
			}
			return negative_num ? counter + 1 : counter;
		}(num);

		assert(digit_count > 0, "I don't know of any numbers with no digits in them");

		// make sure that the string can fit the number
		_data.resize(digit_count);

		// convert the digits to ASCII
		const i64 abs_num = abs(num);
		for (i64 i = digit_count - 1, divisor = 1; i >= 0; --i, divisor *= 10)
			_data[i] = ((abs_num / divisor) % 10) + '0';

		if (num < 0)
			_data[0] = '-';
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
