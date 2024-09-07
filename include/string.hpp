#pragma once

#include "assert.hpp"
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

	class string
	{
	public:
		constexpr string() {};
		string(const char* const str)
		{
			_size = strlen(str);
			capacity = _size;
			_data = new char[_size];

			for (mu64 i = 0; i < _size; ++i)
				_data[i] = str[i];
		}

		constexpr mu64 size() const { return _size; }
		constexpr bool empty() const { return _size == 0; }

		char* data() { return _data; }

		constexpr void clear() { _size = 0; }

		char operator[](u64 index) const
		{
			assert(index < _size, "out-of-bounds string access");
			return _data[index];
		}

		char& operator[](u64 index)
		{
			assert(index < _size, "out-of-bounds string access");
			return _data[index];
		}

		void operator=(const char* const str)
		{
			_size = strlen(str);

			// if the new size is still within the capacity, don't resize the buffer
			if (_size > capacity)
			{
				delete[] _data;
				_data = new char[_size];
			}

			for (mu64 i = 0; i < _size; ++i)
				_data[i] = str[i];
		}

	private:
		mu64 capacity{0};
		mu64 _size{0};
		char* _data{nullptr};
	};
}
