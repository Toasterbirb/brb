#pragma once

#include "array.hpp"
#include "types.hpp"

namespace brb
{
	constexpr mu64 strlen(const char* const str)
	{
		assert(str != nullptr);

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
			assert(_size <= max_size, "string out of capacity");

			for (mu64 i = 0; i < _size; ++i)
				_data[i] = str[i];
		}

		constexpr mu64 size() const { return _size; }
		constexpr mu64 capacity() const { return max_size; }
		constexpr bool empty() const { return _size == 0; }

		char* data() { return _data.data(); }
		void set_size(u64 new_size)
		{
			assert(new_size <= max_size, "the new size is larger than the capacity of the string");
			_size = new_size;
		}

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
			assert(len <= max_size);
			_size = len;

			for (mu64 i = 0; i < len; ++i)
				_data[i] = str[i];
		}

	private:
		mu64 _size;
		array<char, max_size> _data;
	};
}
