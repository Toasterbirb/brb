#pragma once

#include "array.hpp"
#include "types.hpp"

namespace brb
{
	constexpr mu64 strlen(const char* const str)
	{
		ensure(str != nullptr);

		mu64 len{0};
		while (str[len] != '\0')
			++len;
		return len;
	}

	template <u64 max_size>
	class string
	{
	public:
		constexpr string() {};
		constexpr string(const char* const str)
		{
			_size = strlen(str);
			ensure(_size <= max_size, "string out of capacity");

			for (mu64 i = 0; i < _size; ++i)
				_data[i] = str[i];
		}

		constexpr mu64 size() const { return _size; }
		constexpr mu64 capacity() const { return max_size; }
		constexpr bool empty() const { return _size == 0; }
		char* data() { return _data.data(); }

		constexpr void clear() { _size = 0; }

		constexpr char operator[](u64 index) const
		{
			// the array will handle out-of-bounds assertions
			return _data[index];
		}

		constexpr char& operator[](u64 index)
		{
			// the array will handle out-of-bounds assertions
			return _data[index];
		}

		constexpr void operator=(const char* const str)
		{
			// make sure that the str fits into the storage
			u64 len = strlen(str);
			ensure(len <= max_size);
			_size = len;

			for (mu64 i = 0; i < len; ++i)
				_data[i] = str[i];
		}

	private:
		mu64 _size;
		array<char, max_size> _data;
	};
}
